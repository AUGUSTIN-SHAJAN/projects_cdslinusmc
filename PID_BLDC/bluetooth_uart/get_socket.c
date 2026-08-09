#include "main.h"
#include <stdio.h>
#include <sys/socket.h>

int get_rfcomm_socket(int rfcomm_channel,bdaddr_t mac_address_bluetooth)
    {
        
        int sock_fd = socket(AF_BLUETOOTH,SOCK_STREAM,BTPROTO_RFCOMM);
        if(sock_fd < 0)
            {
                perror("socket");
                return -1;
            }
        
        struct sockaddr_rc addr = {0};
        addr.rc_bdaddr = mac_address_bluetooth;
        addr.rc_channel = rfcomm_channel;
        addr.rc_family = AF_BLUETOOTH;

        int ret = connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr));
        if (ret == 0)
            {
                printf("connection successfull\n");
                return sock_fd;
            }
        else
            {
                perror("connect");
                close(sock_fd);
                return -1;
            }
    }
