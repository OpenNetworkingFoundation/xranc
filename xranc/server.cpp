/*
 * Copyright 2019-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Multithreaded, libevent 2.x-based socket server.
 * Copyright (c) 2012 Qi Huang
 * This software is licensed under the BSD license.
 * See the accompanying LICENSE.txt for details.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <signal.h>

#include "spdlog/spdlog.h"

#include "server.h"
#include "client.h"
#include "workqueue.h"
#include "cell_config.h"
#include "dispatch.h"
#include "logger.h"

#define USE_SCTP
#ifdef USE_SCTP
#include <netinet/sctp.h>
#endif

/* Port to listen on. */
#define SERVER_PORT 5555
/* Connection backlog (# of backlogged connections to accept). */
#define CONNECTION_BACKLOG 8
/* Number of worker threads.  Should match number of CPU cores reported in 
 * /proc/cpuinfo. */
#define NUM_THREADS 20

/* Behaves similarly to fprintf(stderr, ...), but adds file, line, and function
 information. */
#define errorOut(...) {\
    fprintf(stderr, "%s:%d: %s():\t", __FILE__, __LINE__, __FUNCTION__);\
    fprintf(stderr, __VA_ARGS__);\
}

static struct event_base *evbase;
static workqueue_t workqueue;

/* Signal handler function (defined below). */
static void sighandler(int signal);

static void closeAndFreeClient(client_t *client) {
    if (client != NULL) {
        closeClient(client);
        if (client->buf_ev != NULL) {
            bufferevent_free(client->buf_ev);
            client->buf_ev = NULL;
        }
        if (client->evbase != NULL) {
            event_base_free(client->evbase);
            client->evbase = NULL;
        }
        /*
        if (client->output_buffer != NULL) {
            evbuffer_free(client->output_buffer);
            client->output_buffer = NULL;
        }
        */
        free(client);
    }
}


/**
 * Called by libevent when there is data to read.
 */
void buffered_on_read(struct bufferevent *bev, void *arg) {
    client_t *client = (client_t *)arg;
    struct evbuffer *input;

    input = bufferevent_get_input(bev);

    while (evbuffer_get_length(input)) {
        int n = evbuffer_remove(input, client->data + client->nbytes, sizeof(client->data) - client->nbytes);
        //log_debug("removed {} bytes", n);
        client->nbytes += n;
    }

    //log_debug("disptaching {} bytes", client->nbytes);

    int r = dispatch((uint8_t *)(client->data), client->nbytes, client);

    if (r) {
        memmove(client->data, client->data + client->nbytes - r, r);
        client->nbytes = r;
    } else {
        client->nbytes = 0;
    }
}

/**
 * Called by libevent when the write buffer reaches 0.  We only
 * provide this because libevent expects it, but we don't use it.
 */
void buffered_on_write(struct bufferevent *bev, void *arg) {
}

/**
 * Called by libevent when there is an error on the underlying socket
 * descriptor.
 */
void buffered_on_error(struct bufferevent *bev, short what, void *arg) {
    closeClient((client_t *)arg);
}

static void server_job_function(struct job *job) {
    client_t *client = (client_t *)job->user_data;

    event_base_dispatch(client->evbase);
    closeAndFreeClient(client);
    free(job);
}

/**
 * This function will be called by libevent when there is a connection
 * ready to be accepted.
 */
void on_accept(evutil_socket_t fd, short ev, void *arg) {
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    workqueue_t *workqueue = (workqueue_t *)arg;
    client_t *client;
    job_t *job;


    client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        warn("accept failed");
        return;
    }

    /* Set the client socket to non-blocking mode. */
    if (evutil_make_socket_nonblocking(client_fd) < 0) {
        warn("failed to set client socket to non-blocking");
        close(client_fd);
        return;
    }

    /* Create a client object. */
    if ((client = (client_t*)malloc(sizeof(*client))) == NULL) {
        warn("failed to allocate memory for client state");
        close(client_fd);
        return;
    }
    memset(client, 0, sizeof(*client));
    client->fd = client_fd;

    /* Add any custom code anywhere from here to the end of this function
     * to initialize your application-specific attributes in the client struct.
     */

    /*
    if ((client->output_buffer = evbuffer_new()) == NULL) {
        warn("client output buffer allocation failed");
        closeAndFreeClient(client);
        return;
    }
    */

    if ((client->evbase = event_base_new()) == NULL) {
        warn("client event_base creation failed");
        closeAndFreeClient(client);
        return;
    }

    /* Shad - try BEV_OPT_DEFER_CALLBACKS */
    client->buf_ev = bufferevent_socket_new(client->evbase, client_fd,
                                            BEV_OPT_CLOSE_ON_FREE);
    if ((client->buf_ev) == NULL) {
        warn("client bufferevent creation failed");
        closeAndFreeClient(client);
        return;
    }
    //bufferevent_set_max_single_write(client->buf_ev, 8192);
    //bufferevent_set_max_single_read(client->buf_ev, 8192);
    bufferevent_setcb(client->buf_ev, buffered_on_read, buffered_on_write,
                      buffered_on_error, client);

    /* We have to enable it before our callbacks will be
     * called. */
    bufferevent_enable(client->buf_ev, EV_READ);

    /* Create a job object and add it to the work queue. */
    if ((job = (job_t*)malloc(sizeof(*job))) == NULL) {
        warn("failed to allocate memory for job state");
        closeAndFreeClient(client);
        return;
    }
    job->job_function = server_job_function;
    job->user_data = client;

    inet_ntop(AF_INET, &(((struct sockaddr_in*)&client_addr)->sin_addr), client->ip, INET_ADDRSTRLEN);
    spdlog::info("connected to {}", client->ip);

    client_timers_add(client);

    workqueue_add_job(workqueue, job);
}

/**
 * Run the server.  This function blocks, only returning when the server has
 * terminated.
 */
int runServer(const Config& config) {
    evutil_socket_t listenfd;
    struct sockaddr_in listen_addr;
    struct event *ev_accept;
    int reuseaddr_on;

    /* Set signal handlers */
    sigset_t sigset;
    sigemptyset(&sigset);
    struct sigaction siginfo;
    siginfo.sa_handler = sighandler,
    siginfo.sa_mask = sigset,
    siginfo.sa_flags = SA_RESTART,
    sigaction(SIGINT, &siginfo, NULL);
    sigaction(SIGTERM, &siginfo, NULL);

    /* Create our listening socket. */
    listenfd = socket(AF_INET, SOCK_STREAM,
#ifdef USE_SCTP
                        IPPROTO_SCTP
#else
                        IPPROTO_TCP
#endif
            );
    if (listenfd < 0) {
        err(1, "listen failed");
    }

    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(SERVER_PORT);
    if (bind(listenfd, (struct sockaddr *)&listen_addr, sizeof(listen_addr)) 
        < 0) {
        err(1, "bind failed");
    }
    if (listen(listenfd, CONNECTION_BACKLOG) < 0) {
        err(1, "listen failed");
    }
    reuseaddr_on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on,
               sizeof(reuseaddr_on));

    /* Set the socket to non-blocking, this is essential in event
     * based programming with libevent. */
    if (evutil_make_socket_nonblocking(listenfd) < 0) {
        err(1, "failed to set server socket to non-blocking");
    }

    if ((evbase = event_base_new()) == NULL) {
        perror("Unable to create socket accept event base");
        close(listenfd);
        return 1;
    }

    /* Initialize work queue. */
    if (workqueue_init(&workqueue, NUM_THREADS)) {
        perror("Failed to create work queue");
        close(listenfd);
        workqueue_shutdown(&workqueue);
        return 1;
    }

    /* We now have a listening socket, we create a read event to
     * be notified when a client connects. */
    ev_accept = event_new(evbase, listenfd, EV_READ|EV_PERSIST,
                          on_accept, (void *)&workqueue);
    event_add(ev_accept, NULL);

    spdlog::info("Server started");

    /* Start the event loop. */
    event_base_dispatch(evbase);

    event_base_free(evbase);
    evbase = NULL;

    close(listenfd);

    printf("Server shutdown.\n");

    return 0;
}

/**
 * Kill the server.  This function can be called from another thread to kill
 * the server, causing runServer() to return.
 */
void killServer(void) {
    fprintf(stdout, "Stopping socket listener event loop.\n");
    if (event_base_loopexit(evbase, NULL)) {
        perror("Error shutting down server");
    }
    fprintf(stdout, "Stopping workers.\n");
    workqueue_shutdown(&workqueue);
}

static void sighandler(int signal) {
    fprintf(stdout, "Received signal %d: %s.  Shutting down.\n", signal,
            strsignal(signal));
    killServer();
}
