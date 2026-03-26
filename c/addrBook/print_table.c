#include "main.h"
static void travel_bintree(personal_info **node)
    {
        if(*node == NULL)
            return;
        travel_bintree(&(*node)->left);
        printf("name: %s num: %ld\n", (*node)->name,(*node)->number);
        travel_bintree(&(*node)->right);
        
    }
status print_table(hash arr[])
    {
        system("clear");
        for(int i = 0; i < HASHLEN; i++)
            {
                if(arr[i].hash_node != NULL)
                    travel_bintree(&arr[i].hash_node);
            }
        printf("Press Enter to exit\n");
        getchar();
            return Add_SUCCESS;
    }