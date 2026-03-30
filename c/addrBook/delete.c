#include "main.h"

static personal_info **findmin(personal_info **node)
    {
        while((*node)->left)
            node = &(*node)->left;
        return node;       
    }
static status travel_bintree(personal_info **node, char *name)
    {
        
        if(*node == NULL)
            {
                printf("This contact doesnt exist\n");
                printf("Press Enter to exit\n");
                getchar();
                return Add_FAIL;
            }
        else if(strcmp(name, (*node)->name) < 0)
            return travel_bintree(&(*node)->left, name);
        else if(strcmp(name, (*node)->name) > 0)
            return travel_bintree(&(*node)->right, name);
        if((*node)->right == NULL && (*node)->left == NULL)
            {
                free((*node)->name);
                free(*node);
                *node = NULL;
            }
        else if(((*node)->right == NULL) ^ ((*node)->left == NULL))
            {
                personal_info *temp = *node;
                *node = (*node)->right == NULL? (*node)->left : (*node)->right;
                free(temp->name);
                free(temp);
            }
        else
            {
                personal_info **temp = findmin(&(*node)->right);
                free((*node)->name);
                (*node)->name = (*temp)->name;
                (*node)->number = (*temp)->number;
                personal_info *hold = *temp;
                *temp = (*temp)->right;
                free(hold);

            }
        return Add_SUCCESS;
    }
status delete_(hash arr[],char *name)
    {
        if(name[0] >= 'a' && name[0] <= 'z')
            travel_bintree(&arr[name[0] - 'a'].hash_node, name);
        else
            travel_bintree(&arr[26].hash_node, name);
        
        return Add_SUCCESS;
    }