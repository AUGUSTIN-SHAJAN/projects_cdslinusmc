#include "serverFunk.h"
#include <unistd.h>

int directmsg(int rec_fd, char *sender_name,char *msg)
    {
        char err = _MSG;
        char sender_name_len = strlen(sender_name);
        char msg_len = strlen(msg);
        char byte = 0;

        byte = write(rec_fd,&err,1);//send code
        if(byte<1) return -1;
        byte = write(rec_fd,&sender_name_len,1);//send senderlen
        if(byte<1) return -1;
        byte = write(rec_fd,sender_name,sender_name_len);//send sender
        if(byte<1) return -1;
        byte = write(rec_fd,&msg_len,1);//send msglen
        if(byte<1) return -1;
        byte = write(rec_fd,msg,msg_len);//send msg
        if(byte<1) return -1;
        return 1;
}
        