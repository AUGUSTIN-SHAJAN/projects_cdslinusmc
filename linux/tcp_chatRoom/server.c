#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>

#define MAX_CLIENTS 50
#define SERVER_PORT 9990
int main()
    {
        int listening_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(listening_sock_fd == -1)
            {
                perror("socket");
                return -1;
            }
        int flags = fcntl(listening_sock_fd, F_GETFL, 0);
        fcntl(listening_sock_fd, F_SETFL, flags | O_NONBLOCK);//create non-blocking socket


        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        server_addr.sin_addr.s_addr = INADDR_ANY;
        if(bind(listening_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
            {
                perror("bind");
                return -1;
            }//bind ip:port to scoket

        listen(listening_sock_fd,MAX_CLIENTS);//set max clients



        int epollfd = epoll_create1(0);
        if (epollfd == -1) {
             perror("epoll_create1");
             return -1;
         }//create epoll instance

        struct epoll_event ev;
        
        ev.events = EPOLLIN;
        ev.data.fd = listening_sock_fd;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listening_sock_fd, &ev) == -1) {
            perror("epoll_ctl: listen_sock");
            return -1;
        }//attach server_fd to epoll

        struct epoll_event events[MAX_CLIENTS];

        while(1)
            {
                int nfds = epoll_wait(epollfd, events, MAX_CLIENTS, -1);
                if (nfds == -1)
                    {
                        perror("epoll_wait");
                        return -1;
                    }
                for(int i = 0; i < nfds; i++)
                    {
                        if(events[i].data.fd == listening_sock_fd)
                            {
                                struct sockaddr_in server_addr_client;
                                memset(&server_addr_client, 0, sizeof(server_addr_client));
                                socklen_t server_addr_client_len = sizeof(server_addr_client);
                                int client_fd = accept4(listening_sock_fd,  (struct sockaddr *)&server_addr_client, &server_addr_client_len ,SOCK_NONBLOCK);
                                if (client_fd == -1)
                                    {
                                        perror("accept4");
                                        continue;
                                    }
                                char ip[INET_ADDRSTRLEN];
                                inet_ntop(AF_INET, &server_addr_client.sin_addr, ip, sizeof(ip));
                                printf("Client %s:%d connected\n", ip,ntohs(server_addr_client.sin_port));//accept client

                                ev.events = EPOLLIN;
                                ev.data.fd = client_fd;
                                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, client_fd, &ev) == -1)
                                    {
                                        perror("epoll_ctl: conn_sock");
                                        continue;
                                    }//add to epoll
                            }
                        else
                            {
                                if(events[i].events & (EPOLLHUP | EPOLLRDHUP | EPOLLERR))
                                    {
                                        printf("client disconnected\n");
                                        if(epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, NULL) == -1)
                                            {
                                                perror("epoll_ctl");
                                            }
                                        close(events[i].data.fd);
                                        continue;
                                    }
                                if(events[i].events & EPOLLIN)
                                    {
                                        char buffer[90];
                                        int byte = read(events[i].data.fd,buffer,90);
                                        if(byte > 0)
                                            {
                                                buffer[byte] = 0;
                                                printf("%s\n",buffer);
                                            }
                                        else// if read returns 0 or -1 even if blocking or nonblocking, disconnect, in epoll
                                            {
                                                printf("client disconnected\n");
                                                if(epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, NULL) == -1)
                                                    {
                                                        perror("epoll_ctl");
                                                    }
                                                close(events[i].data.fd);
                                            }
                                        continue;
                                    }
                            }
                    }
            }
    }