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

#ifndef _context_H
#define _context_H

#include <pthread.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <XRANCPDU.h>

/**
 * Struct to carry around context (context)-specific data.
 */
typedef struct context {
    pthread_t thread;

    /* The context's socket. */
    int fd;

    /* The event_base for this context. */
    struct event_base *evbase;

    /* The bufferedevent for this context. */
    struct bufferevent *buf_ev;

    /* The output buffer for this context. */
    //struct evbuffer *output_buffer;

    /* Here you can add your own application-specific attributes which
     * are context-specific. */

    /*  IP address of this context */
    char ip[INET_ADDRSTRLEN];

    char server_ip[INET_ADDRSTRLEN];
    int port;
    int num_ues;
    int enb_index;
    bool connected;
    struct event *ue_admission_timer;
    char data[8192];
    int nbytes;
} context_t;

void ctx_close(context_t *context);
void ctx_send(XRANCPDU *pdu, context_t *context);
#endif
