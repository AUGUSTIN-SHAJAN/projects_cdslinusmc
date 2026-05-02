#include "../main.h"
static void travel_bintree(user_personal_info **node)
    {
        if(*node == NULL)
            return;
        printf("name: %s pass: %s\n", (*node)->uname,(*node)->password);
        travel_bintree(&(*node)->left);
        travel_bintree(&(*node)->right);
        
    }
userCRUD print_table(user_store_hash arr[])
    {
        for(int i = 0; i < userCRUD_HASHLEN; i++)
            {
                if(arr[i].hash_node != NULL)
                    travel_bintree(&arr[i].hash_node);
            }
            return SUCCESS;
    }