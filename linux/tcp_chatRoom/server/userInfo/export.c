#include "../main.h"
#include "userInfo.h"

static void travel_bintree(user_personal_info **node, int fd)
    {
        if(*node == NULL)
            return;
        write(fd, (*node)->uname, strlen((*node)->uname));
        write(fd, ",", 1);
        write(fd, (*node)->password, strlen((*node)->password));
        write(fd, "\n", 1);
        travel_bintree(&(*node)->left,fd);
        travel_bintree(&(*node)->right,fd);
        
    }
userCRUD export_(user_store_hash arr[], char *filename)
    {
        
        int fd = parse_file(filename, "csv", 'w');
        if(fd ==-1)
            {
                return FAIL;
            }
            
        write(fd,"uname,password\n",15);
        for(int i = 0; i < userCRUD_HASHLEN; i++)
            {
                if(arr[i].hash_node != NULL)
                    travel_bintree(&arr[i].hash_node,fd);
            }
        
            return SUCCESS;
    }