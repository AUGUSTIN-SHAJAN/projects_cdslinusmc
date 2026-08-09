
#include "userInfo.h"
static int travel_bintree(user_personal_info **node, char *uname)
    {
        
        if(*node == NULL)
            {
                printf("Not found\n");
                return -1;
            }
        else if(strcmp(uname, (*node)->uname) < 0)
            return travel_bintree(&(*node)->left,uname);
        else if(strcmp(uname, (*node)->uname) > 0)
            return travel_bintree(&(*node)->right,uname);
        else
            {
                printf("name: %s pass: %s\n", (*node)->uname,(*node)->password);
                return (*node)->fd;
            }
            
    }
int search(user_store_hash arr[], char *uname)
    {
        
        if(uname[0] >= 'a' && uname[0] <= 'z')
            return travel_bintree(&arr[uname[0] - 'a'].hash_node, uname);
        else
            return travel_bintree(&arr[26].hash_node, uname);
        
    }