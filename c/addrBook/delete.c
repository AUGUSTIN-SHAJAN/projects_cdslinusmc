#include "main.h"
static int re_attach=0,exec_once=0;


static personal_info **rightmin(personal_info **node, char *name, long num)
    {
        if((*node)->left == NULL)
            {
                if((*node)->right != NULL)
                    re_attach =1;
                exec_once = 1;
                return node;
            }
        else
            {
                personal_info ** temp = rightmin(&(*node)->left, name, num);
                if(re_attach)
                    {
                        (*node)->left = (*node)->left->right;
                        re_attach= 0;
                    }
                else if(exec_once)
                    {
                        (*node)->left = NULL;
                        exec_once = 0;
                    }
                return temp;
            }
    }
static personal_info **leftmax(personal_info **node,char *name, long num)
    {
        if((*node)->right == NULL)
            {
                if((*node)->left != NULL)
                    re_attach=1;
                return node;
            }
            
        else
            {
                personal_info ** temp = leftmax(&(*node)->right,  name, num);
                if(re_attach)
                    {
                        (*node)->right = (*node)->right->left;
                        re_attach = 0;
                    }
                else if(exec_once)
                    {
                        (*node)->right = NULL;
                        exec_once = 0;
                    }
                 return temp;
            }
            
    }

 static personal_info **find_replacement(personal_info **node, char *name, long num)
    {
        if((*node)->right != NULL)
            return rightmin(&(*node)->right,  name, num);
        else if ((*node)->left != NULL)
            return leftmax(&(*node)->left, name, num);
        else
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
        else
            {
                personal_info **temp = find_replacement(node,name,(*node)->number);
                //(*node)->right = (*temp)->right;
                // (*node)->left = (*temp)->left;
                (*node)->number = (*temp)->number;
                free((*node)->name);
                (*node)->name= (*temp)->name;
                free(*temp);
                *temp = NULL;
                return Add_SUCCESS;
            }
            
    }
status delete_(hash arr[],char *name)
    {
        if(name[0] >= 'a' && name[0] <= 'z')
            travel_bintree(&arr[name[0] - 'a'].hash_node, name);
        else
            travel_bintree(&arr[26].hash_node, name);
        
        return Add_SUCCESS;
    }