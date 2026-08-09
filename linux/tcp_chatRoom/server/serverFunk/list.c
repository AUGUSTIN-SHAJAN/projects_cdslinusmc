#include "serverFunk.h"
#include <string.h>
#include <unistd.h>
static void travel_bintree(user_personal_info **node,char *sender_name,char code)
    {
        if(*node == NULL)
            return;
        //directmsg((*node)->fd, sender_name, msg);
        int sock_fd = (*node)->fd;
        int byte = write(sock_fd, &code, 1);//send online/offline code
        if(byte<1)goto err;
        char sender_len = strlen(sender_name);
        byte = write(sock_fd,&sender_len,1);//send sender len
        if(byte<1)goto err;
        byte = write(sock_fd,sender_name,sender_len);//send sender
        err:
        travel_bintree(&(*node)->left,sender_name,code);
        travel_bintree(&(*node)->right,sender_name,code);
        
    }
userCRUD list(user_store_hash online[],char *sender_name, char code)
    {
        for(int i = 0; i < userCRUD_HASHLEN; i++)
            {
                if(online[i].hash_node != NULL)
                    travel_bintree(&online[i].hash_node,sender_name,code);
            }
            return SUCCESS;
    }