#include "main.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int parse_file(char *filename)
    {
        char *fstr =strdup(filename);
        strmat temp = strtomat(fstr, '.');
        if(temp.argc != 2)
            {
                printf("Format:<filename>.csv\n");
                return -1;
            }
        if(strcmp(temp.argv[1],"csv"))
            {
                printf("csv file only\n");
                return -1;
            }

        free(fstr);
        free(temp.argv);
        int fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0744);
        if(fd == -1)
            {
                
                char ch;
                printf("overwrite %s?(y/n)\n",filename);
                scanf("%c",&ch);
                if(ch == 'y')
                    fd = open(filename , O_WRONLY | O_TRUNC);
                if(fd == -1)
                    printf("error opening file\n");
            }
        return fd;
    }

static void travel_bintree(personal_info **node, int fd)
    {
        if(*node == NULL)
            return;
        travel_bintree(&(*node)->left,fd);
        char buffer[65]={0};
        write(fd, (*node)->name, strlen((*node)->name));
        write(fd, ",", 1);
        sprintf(buffer,"%ld",(*node)->number);
        write(fd, buffer, strlen(buffer));
        travel_bintree(&(*node)->right,fd);
        
    }
status export_(hash arr[], char *filename)
    {
        
        int fd = parse_file(filename);
        if(fd ==-1)
            {
                printf("Press Enter to exit\n");
                getchar();
                return Add_FAIL;
            }
            
        write(fd,"Name,Number\n",12);
        for(int i = 0; i < 9; i++)
            {
                if(arr[i].hash_node != NULL)
                    travel_bintree(&arr[i].hash_node,fd);
            }
        
            return Add_SUCCESS;
    }