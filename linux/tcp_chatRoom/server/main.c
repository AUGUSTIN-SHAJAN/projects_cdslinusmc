#include "main.h"
#include "userInfo/userInfo.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>

conStat *mallocDestat(int fd)
    {
        conStat *temp = malloc(sizeof(*temp));
        if(temp)
            {
                temp->client = NULL;
                temp->fd =fd;
                return temp;
            }
        return NULL;
    }

int chnFcntl(int sock_fd, int behaviour)
    {
        int flags = fcntl(sock_fd, F_GETFL, 0);

        if (flags == -1) {
            perror("fcntl F_GETFL");
            return -1;
        }
        
        if (fcntl(sock_fd, F_SETFL, (behaviour == O_NONBLOCK)? flags | behaviour : flags & behaviour) == -1) {
            perror("fcntl F_SETFL");
            return -1;
        }
    return 1;
    }


int main()
    {
        user_store_hash users[userCRUD_HASHLEN]={0};
        user_store_hash online[userCRUD_HASHLEN]={0};
        import_(users, "lx.csv");
        int listening_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(listening_sock_fd == -1)
            {
                perror("socket");
                return -1;
            }
        int opt = 1;
    setsockopt(listening_sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
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
                                int client_fd = accept4(listening_sock_fd,  (struct sockaddr *)&server_addr_client, &server_addr_client_len ,0);
                                if (client_fd == -1)
                                    {
                                        perror("accept4");
                                        continue;
                                    }
                                char ip[INET_ADDRSTRLEN];
                                inet_ntop(AF_INET, &server_addr_client.sin_addr, ip, sizeof(ip));
                                printf("Client %s:%d connected\n", ip,ntohs(server_addr_client.sin_port));//accept client
                                struct  epoll_event temp_ev;
                                temp_ev.events = EPOLLIN ;
                                temp_ev.data.ptr = mallocDestat(client_fd);
                                 printf("dim\n");
                                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, client_fd, &temp_ev) == -1)
                                    {
                                        perror("epoll_ctl: conn_sock");
                                        continue;
                                    }//add to epoll
                                   
                            }
                        else
                            {
                                
                                
                                if(events[i].events & (EPOLLHUP | EPOLLRDHUP | EPOLLERR))
                                    goto error;
                                if(events[i].events & EPOLLIN)
                                    { 
                                        
                                        char buffer[150];
                                        if(1)
                                            {
                                                int byte = read(((conStat*)(events[i].data.ptr))->fd,buffer,1);
                                                if(byte == 0)
                                                    goto error;
                                                buffer[byte] = 0;
                                                if(byte == 1)
                                                    {
                                                        switch(buffer[0])
                                                            {
                                                                case _LOGIN:
                                                                    {
                                                                        
                                                                        ((conStat*)(events[i].data.ptr))->client = login(((conStat*)(events[i].data.ptr))->fd,online,users);
                                                                        if(((conStat*)(events[i].data.ptr))->client)
                                                                            {
                                                                                char err = _LOGIN_SUCCESS;
                                                                                write(((conStat*)(events[i].data.ptr))->fd,&err,1);
                                                                                printf("pasux\n");
                                                                                list(online, ((user_personal_info*)(((conStat*)(events[i].data.ptr))->client))->uname, _ONLINE_LIST);
                                                                            }
                                                                        else
                                                                            {
                                                                                char err = _LOGIN_FAIL;
                                                                                write(((conStat*)(events[i].data.ptr))->fd,&err,1);
                                                                                printf("pasrong\n");
                                                                            }
                                                                        break;
                                                                    }
                                                                case _BROADCAST:
                                                                    if(((conStat*)(events[i].data.ptr))->client)
                                                                        {
                                                                            char uname_len,msg_len;
                                                                            int byte;
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd, (char*)&uname_len, 1);//read strlen_uname
                                                                            if(!(byte>0))   goto looper;
                                                                            char uname[uname_len + 1];
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd,uname,uname_len);//read unamee
                                                                            if(!(byte>0)) goto looper;
                                                                            uname[byte]=0;
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd, (char*)&msg_len, 1);//read msglen
                                                                            if(!(byte>0)) goto looper;
                                                                            char msg[msg_len + 1];
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd,msg,msg_len);///read msg
                                                                            if(!(byte>0)) goto looper;
                                                                            msg[byte]=0;
                                                                            printf("%s->%s\n",msg,uname);
                                                                            broadcast(online, uname, msg);
                                                                        }
                                                                    break;
                                                                case _DIRECTMSG:
                                                                    if(((conStat*)(events[i].data.ptr))->client)
                                                                        {
                                                                            char uname_len,msg_len;
                                                                            int byte;
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd, (char*)&uname_len, 1);//read strlen_uname
                                                                            if(!(byte>0))
                                                                                {
                                                                                    looper:
                                                                                    printf("sender disconnected\n");
                                                                                    goto error;
                                                                                }
                                                                            char uname[uname_len + 1];
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd,uname,uname_len);//read unamee
                                                                            if(!(byte>0)) goto looper;
                                                                            uname[byte]=0;
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd, (char*)&msg_len, 1);//read msglen
                                                                            if(!(byte>0)) goto looper;
                                                                            char msg[msg_len + 1];
                                                                            byte = read(((conStat*)(events[i].data.ptr))->fd,msg,msg_len);///read msg
                                                                            if(!(byte>0)) goto looper;
                                                                            msg[byte]=0;
                                                                            printf("%s->%s\n",msg,uname);
                                                                            int rec_fd = search(online, uname);
                                                                            if(rec_fd == -1)
                                                                                {
                                                                                    err:
                                                                                    {char err = _REC_NA;
                                                                                    write(((conStat*)(events[i].data.ptr))->fd, &err, 1);
                                                                                       }
                                                                            }
                                                                            else
                                                                                {
                                                                                    if(directmsg(rec_fd, ((user_personal_info*)(((conStat*)(events[i].data.ptr))->client))->uname, msg) == -1)
                                                                                        goto err;
                                                                                }
                                                                            
                                                                        }
                                                                    break;
                                                            }
                                                    }
                                                else
                                                    goto error;
                                            }
                                        else// if read returns 0 or -1 even if blocking or nonblocking, disconnect, in epoll
                                            {
                                                error:
                                                    printf("client disconnected\n");
                                                    list(online, ((user_personal_info*)(((conStat*)(events[i].data.ptr))->client))->uname, _OFFLINE_LIST);
                                                    if(((conStat*)(events[i].data.ptr))->client)
                                                        {
                                                            delete_(online, ((user_personal_info*)(((conStat*)(events[i].data.ptr))->client))->uname);
                                                        }
                                                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, ((conStat*)(events[i].data.ptr))->fd, NULL) == -1)
                                                        {
                                                            perror("epoll_ctl");
                                                        }
                                                    
                                                    close(((conStat*)(events[i].data.ptr))->fd);
                                                    free(events[i].data.ptr);
                                                    events[i].data.ptr = NULL;
                                            }
                                        continue;
                                    }
                            }
                    }
            }
    }
