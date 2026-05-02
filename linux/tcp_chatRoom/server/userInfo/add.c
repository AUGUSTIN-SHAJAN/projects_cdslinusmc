#include "../main.h"
#include "userInfo.h"
#include <stdio.h>
#include <string.h>



static user_personal_info *alloc(char *password, char *uname)
    {
        user_personal_info *temp = malloc(sizeof(*temp));
        if(temp == NULL)
            return NULL;
        temp->left = temp->right = NULL;
        temp->uname = strdup(uname);
        temp->password = strdup(password);
        return temp;
    }
static userCRUD travel_bintree(user_personal_info **node, char *password, char *uname)
    {
        
        if(*node == NULL)
            {
                *node = alloc(password, uname);
                return SUCCESS;
            }
        else if(strcmp(uname, (*node)->uname) < 0)
            return travel_bintree(&(*node)->left,password,uname);
        else if(strcmp(uname, (*node)->uname) > 0)
            return travel_bintree(&(*node)->right,password,uname);
        else
            {
                printf("This user exist\n");
                return FAIL;
            }
            
    }
userCRUD add(user_store_hash arr[],char *password, char *uname)

    {
        if(strlen(password) < 4 || strlen(uname) < 4)
            {
                printf("Minimum length 4 for both name and password\n");
                return FAIL;
            }
        if(uname[0] >= 'a' && uname[0] <= 'z')
            return travel_bintree(&arr[uname[0] - 'a'].hash_node, password, uname);
        else
            return travel_bintree(&arr[26].hash_node, password, uname);
    }