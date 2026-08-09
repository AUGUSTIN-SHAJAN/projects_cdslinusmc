#include "serverFunk.h"
static void travel_bintree(user_personal_info **node,char *sender_name,char *msg)
    {
        if(*node == NULL)
            return;
        directmsg((*node)->fd, sender_name, msg);
        travel_bintree(&(*node)->left,sender_name,msg);
        travel_bintree(&(*node)->right,sender_name,msg);
        
    }
userCRUD broadcast(user_store_hash online[],char *sender_name,char *msg)
    {
        for(int i = 0; i < userCRUD_HASHLEN; i++)
            {
                if(online[i].hash_node != NULL)
                    travel_bintree(&online[i].hash_node,sender_name,msg);
            }
            return SUCCESS;
    }