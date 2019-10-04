
#define USE_SCTP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <boost/log/trivial.hpp>
#include <server.h>

using namespace std;

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifdef USE_SCTP
#include <netinet/sctp.h>
#endif

#define SIZE 1024
char buf[SIZE];
#define ECHO_PORT 2013

int server_main() {
        int sockfd, client_sockfd;
        int nread;
        struct sockaddr_in serv_addr;

        cout << "SCTP server" << endl;

        /* create endpoint using TCP or SCTP */
        sockfd = socket(AF_INET, SOCK_STREAM,
#ifdef USE_SCTP
                        IPPROTO_SCTP
#else
                        IPPROTO_TCP
#endif
                );
        if (sockfd < 0) {
            perror("socket creation failed");
            exit(2);
        }
        /* bind address */
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(ECHO_PORT);
        if (bind(sockfd,
                 (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0) {
            perror("bind failed");
            exit(3);
        }
        /* specify queue length */
        listen(sockfd, 5);
        for (;;) {
                /* get a connection from client */
                client_sockfd = accept(sockfd,
                                       (struct sockaddr *) NULL,
                                       (unsigned int *) NULL);
                if (client_sockfd == -1) {
                        perror("accept failed");
                        continue;
                }

                cout << "client connected" << endl;

                /* transfer data */
                nread = read(client_sockfd, buf, SIZE);
                /* write to stdout */
                write(1, buf, nread);
                /* and echo it back to client */
                write(client_sockfd, buf, nread);
                /* no more for this client */
                close(client_sockfd);
        }
}
