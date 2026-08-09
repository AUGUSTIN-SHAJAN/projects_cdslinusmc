#include "clientFunk.h"
#include <fcntl.h>

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

