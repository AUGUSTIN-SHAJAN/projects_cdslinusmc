
#include "userInfo.h"
static user_personal_info **findmin(user_personal_info **node)
    {
        while((*node)->left)
            node = &(*node)->left;
        return node;       
    }
static userCRUD travel_bintree(user_personal_info **node, char *uname)
    {
        
        if(*node == NULL)
            {
                printf("This User doesnt exist\n");
                return FAIL;
            }
        else if(strcmp(uname, (*node)->uname) < 0)
            return travel_bintree(&(*node)->left, uname);
        else if(strcmp(uname, (*node)->uname) > 0)
            return travel_bintree(&(*node)->right, uname);
        if((*node)->right == NULL && (*node)->left == NULL)
            {
                free((*node)->uname);
                free((*node)->password);
                free(*node);
                *node = NULL;
            }
        else if(((*node)->right == NULL) ^ ((*node)->left == NULL))
            {
                user_personal_info *temp = *node;
                *node = (*node)->right == NULL? (*node)->left : (*node)->right;
                free(temp->uname);
                free(temp->password);
                free(temp);
            }
        else
            {
                printf("%p\n",node);
                user_personal_info **temp = findmin(&(*node)->right);
                printf("%p\n",temp);
                free((*node)->uname);
                free((*node)->password);
                (*node)->uname = (*temp)->uname;
                (*node)->password = (*temp)->password;
                user_personal_info *hold = *temp;
                *temp = (*temp)->right;
                free(hold);
                printf("User removed\n\n");
            }
        return SUCCESS;
    }
userCRUD delete_(user_store_hash arr[],char *uname)
    {
        if(uname[0] >= 'a' && uname[0] <= 'z')
            return travel_bintree(&arr[uname[0] - 'a'].hash_node, uname);
        else
            return travel_bintree(&arr[26].hash_node, uname);
    }