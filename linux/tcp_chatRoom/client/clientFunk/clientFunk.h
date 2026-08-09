#ifndef CCC
#define CCC
#include <stdio.h>
#include "../../../../lib/input/input.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>

typedef enum
    {
        _LOGIN,
        _BROADCAST,
        _DIRECTMSG,
        
    }client_req;

typedef enum
    {
        _ONLINE_LIST,
        _OFFLINE_LIST,
        _MSG,
        _LOGIN_FAIL,
        _LOGIN_SUCCESS,
        _REC_NA
    }server_ack;

server_ack login(int sock_fd);
int chnFcntl(int sock_fd, int behaviour);

#endif