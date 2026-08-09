
#include "userInfo.h"


static user_personal_info *alloc(char *password, char *uname,int fd)
    {
        user_personal_info *temp = malloc(sizeof(*temp));
        if(temp == NULL)
            return NULL;
        temp->left = temp->right = NULL;
        temp->uname = strdup(uname);
        temp->password = strdup(password);
        temp->fd =fd;
        return temp;
    }
static user_personal_info *travel_bintree(user_personal_info **node, char *password, char *uname, int fd)
    {
        
        if(*node == NULL)
            {
                *node = alloc(password, uname,fd);
                return *node;
            }
        else if(strcmp(uname, (*node)->uname) < 0)
            return travel_bintree(&(*node)->left,password,uname,fd);
        else if(strcmp(uname, (*node)->uname) > 0)
            return travel_bintree(&(*node)->right,password,uname,fd);
        else
            {
                if(strcmp(password, (*node)->password))
                    return NULL;
                return *node;
            }
            
    }
user_personal_info *add(user_store_hash arr[],char *password, char *uname,int fd)

    {
        if(strlen(password) < 4 || strlen(uname) < 4)
            {
                printf("Minimum length 4 for both name and password\n");
                return NULL;
            }
        if(uname[0] >= 'a' && uname[0] <= 'z')
            return travel_bintree(&arr[uname[0] - 'a'].hash_node, password, uname, fd);
        else
            return travel_bintree(&arr[26].hash_node, password, uname,fd);
    }