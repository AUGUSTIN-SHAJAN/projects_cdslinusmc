#ifndef SSS
#define SSS
#define _GNU_SOURCE

#include "userInfo/userInfo.h"
#include "serverFunk/serverFunk.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>

#define MAX_CLIENTS 1000
#define SERVER_PORT 9990

typedef struct conStat
    {
        user_personal_info *client;
        int fd;
    }conStat;



#endif