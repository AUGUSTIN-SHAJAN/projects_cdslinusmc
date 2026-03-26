#include "main.h"
static status travel_bintree(personal_info **node, char *name)
    {
        
        if(*node == NULL)
            {
                printf("Not found\n");
                return Add_FAIL;
            }
        else if(strcmp(name, (*node)->name) < 0)
            return travel_bintree(&(*node)->left,name);
        else if(strcmp(name, (*node)->name) > 0)
            return travel_bintree(&(*node)->right,name);
        else
            {
                printf("name: %s num: %ld\n", (*node)->name,(*node)->number);
                return Add_SUCCESS;
            }
            
    }
status search(hash arr[], char *name)
    {
        
        if(name[0] >= 'a' && name[0] <= 'z')
            travel_bintree(&arr[name[0] - 'a'].hash_node, name);
        else
            travel_bintree(&arr[26].hash_node, name);
        
        return Add_SUCCESS;
    }