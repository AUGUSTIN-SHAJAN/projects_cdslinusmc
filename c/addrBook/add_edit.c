#include "main.h"



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
        else if(strcmp(name, (*node)->name) < 0)
            return travel_bintree(&(*node)->left,num,name);
        else if(strcmp(name, (*node)->name) > 0)
            return travel_bintree(&(*node)->right,num,name);
        else
            {
                (*node)->number =num;
                return Add_FAIL;
            }
            
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
        if(name[0] >= 'a' && name[0] <= 'z')
            travel_bintree(&arr[name[0] - 'a'].hash_node, num, name);
        else
            travel_bintree(&arr[26].hash_node, num, name);
        
        return Add_SUCCESS;
    }