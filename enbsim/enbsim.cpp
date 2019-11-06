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

static int create_bind_socket(int enb_id) {

    char ip[18];
    int fd;
    struct sockaddr_in localaddr;

    fd = socket(AF_INET, SOCK_STREAM,
#ifdef USE_SCTP
                            IPPROTO_SCTP
#else
                            IPPROTO_TCP
#endif
                        );


    sprintf(ip, "127.0.0.%d", enb_id);
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(ip);
    localaddr.sin_port = 0;  // Any local port will do

    bind(fd, (struct sockaddr *)&localaddr, sizeof(localaddr));

    return fd;
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
    int i;

    if (argc != 5) {
        fprintf(stderr, "Usage: enbsim <ip> <port> <num-enbs>\n");
        return 1;
    }

    char *server_ip  = argv[1];
    int port = atoi(argv[2]);
    int session_count = atoi(argv[3]);

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &(sin.sin_addr));
    sin.sin_port = htons(port);

    struct event_base *evbase;
	evbase = event_base_new();
	if (!evbase) {
		puts("Couldn't open event base");
		return 1;
	}

    for (i = 0; i < session_count; ++i) {
		context_t *context;
		if ((context = (context_t*)malloc(sizeof(*context))) == NULL) {
		  printf("failed to allocate memory for client state");
		  return 1;
		}
		context->evbase = evbase;
		context->fd = create_bind_socket(i + 1);
		context->buf_ev = bufferevent_socket_new(context->evbase, context->fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(context->buf_ev, readcb, NULL, eventcb, context);
        bufferevent_enable(context->buf_ev, EV_READ|EV_WRITE);
        if (bufferevent_socket_connect(context->buf_ev, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
          /* Error starting connection */
          bufferevent_free(context->buf_ev);
          puts("error connect");
          return -1;
        }
    }

    event_base_dispatch(evbase);

    event_base_free(evbase);

    printf("%zd total bytes read\n", total_bytes_read);
    printf("%zd total messages read\n", total_messages_read);
    printf("%.3f average messages size\n",
            (double)total_bytes_read / total_messages_read);

    return 0;
}
