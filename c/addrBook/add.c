#include "main.h"
#include <stdlib.h>
#include <string.h>

static personal_info *alloc(long num, char *name)
    {
        personal_info *temp = malloc(sizeof(*temp));
        if(temp == NULL)
            return NULL;
        temp->left = temp->prev = temp->right = NULL;
        temp->name = strdup(name);
        temp->number = num;
        return temp;
    }
static status travel_bintree(personal_info **node, long num, char *name)
    {
        if(*node == NULL)
            {
                *node = alloc(num, name);
                return Add_SUCCESS;
            }
        else if(num < (*node)->number)
            return travel_bintree(&(*node)->left,num,name);
        else if(num > (*node)->number)
            return travel_bintree(&(*node)->right,num,name);
        else
            return Add_FAIL;
    }
status add(hash arr[],char *ph_num, char *name)
    {
        char *temp;
        long num = strtol(ph_num, &temp, 10);
        if( num < 1000000000L || num > 9999999999L)
            {
                printf("Enter a 10 digit phone number\n");
                return Add_FAIL;
            }
        travel_bintree(&arr[ph_num[0] - '0'].hash_node, num, name);
        return Add_SUCCESS;
    }