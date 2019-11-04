#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define USE_SCTP
#ifdef USE_SCTP
#include <netinet/sctp.h>
#endif

#include <string.h>
#include <stdlib.h>

#include "context.h"
#include "dispatch.h"
#include "config.h"

int64_t total_bytes_read = 0;
int64_t total_messages_read = 0;

static void set_tcp_no_delay(evutil_socket_t fd)
{
    int one = 1;
    setsockopt(fd,
#ifdef USE_SCTP
                IPPROTO_SCTP,
#else
                IPPROTO_TCP,
#endif
                TCP_NODELAY, &one, sizeof one);
}

static void timeoutcb(evutil_socket_t fd, short what, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
    printf("timeout\n");

    event_base_loopexit(base, NULL);
}

static void readcb(struct bufferevent *bev, void *arg)
{
    context_t *ctx = (context_t *)arg;
    char data[4096];
    int nbytes;
    int tbytes = 0;

    /* This callback is invoked when there is data to read on bev. */
    struct evbuffer *input = bufferevent_get_input(bev);
    while (evbuffer_get_length(input) > 0) {
        /* Remove a chunk of data from the input buffer, copying it into our
         * local array (data). */
        nbytes = evbuffer_remove(input, data, 4096);
        /* Add the chunk of data from our local array (data) to the client's
         * output buffer. */
        //evbuffer_add(client->output_buffer, data, nbytes);
        tbytes += nbytes;
    }

    dispatch((uint8_t *)data, tbytes, ctx);

    struct evbuffer *output = bufferevent_get_output(bev);

    ++total_messages_read;
    total_bytes_read += tbytes;

    /* Copy all the data from the input buffer to the output buffer. */
    evbuffer_add_buffer(output, input);
}

static void eventcb(struct bufferevent *bev, short events, void *ptr)
{
    if (events & BEV_EVENT_CONNECTED) {
        evutil_socket_t fd = bufferevent_getfd(bev);
        set_tcp_no_delay(fd);
    } else if (events & BEV_EVENT_ERROR) {
        printf("NOT Connected\n");
    }
}

int enbsim_main(int argc, char **argv, const Config& config)
{
    //struct bufferevent **bevs;
    struct sockaddr_in sin;
    struct event *evtimeout;
    struct timeval timeout;
    int i;

    if (argc != 5) {
        fprintf(stderr, "Usage: client <ip> <port> <sessions> <time>\n");
        return 1;
    }

    char *server_ip  = argv[1];
    int port = atoi(argv[2]);
    int session_count = atoi(argv[3]);
    int seconds = atoi(argv[4]);
    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;

    /* Create a context object. */
    context_t *context;
    if ((context = (context_t*)malloc(sizeof(*context))) == NULL) {
      printf("failed to allocate memory for client state");
      return 1;
    }

    context->fd = socket(AF_INET, SOCK_STREAM,
#ifdef USE_SCTP
                            IPPROTO_SCTP
#else
                            IPPROTO_TCP
#endif
                        );

    context->evbase = event_base_new();
    if (!context->evbase) {
        puts("Couldn't open event base");
        return 1;
    }

    evtimeout = evtimer_new(context->evbase, timeoutcb, context->evbase);
    evtimer_add(evtimeout, &timeout);

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &(sin.sin_addr));
    sin.sin_port = htons(port);

    //bevs = (struct bufferevent **)malloc(session_count * sizeof(struct bufferevent *));
    for (i = 0; i < session_count; ++i) {
        context->buf_ev = bufferevent_socket_new(context->evbase, context->fd, BEV_OPT_CLOSE_ON_FREE);

        bufferevent_setcb(context->buf_ev, readcb, NULL, eventcb, context);
        bufferevent_enable(context->buf_ev, EV_READ|EV_WRITE);
        //evbuffer_add(bufferevent_get_output(context->buf_ev), message, block_size);

        if (bufferevent_socket_connect(context->buf_ev, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
          /* Error starting connection */
          bufferevent_free(context->buf_ev);
          puts("error connect");
          return -1;
        }
        //bevs[i] = context->buf_ev;
    }

    event_base_dispatch(context->evbase);

    for (i = 0; i < session_count; ++i) {
        //bufferevent_free(bevs[i]);
    }
    //free(bevs);
    event_free(evtimeout);
    event_base_free(context->evbase);
    //free(message);

    printf("%zd total bytes read\n", total_bytes_read);
    printf("%zd total messages read\n", total_messages_read);
    printf("%.3f average messages size\n",
            (double)total_bytes_read / total_messages_read);
    printf("%.3f MiB/s throughtput\n",
            (double)total_bytes_read / (timeout.tv_sec * 1024 * 1024));

    return 0;
}

