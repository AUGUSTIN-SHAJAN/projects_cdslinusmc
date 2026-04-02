#include "parse_file.h"

int parse_file(char *filename, char *extension, char filemode)
    {
        if(strlen(extension) == 0)
            goto skip;
        char *destr_str = strdup(filename);
        strmat temp = strtomat(destr_str, '.');
        if(strcmp(temp.argv[temp.argc-1], extension))
            {
                printf("Wrong extension\n");
                free(destr_str);
                free(temp.argv);
                return -1;
            }
        free(destr_str);
        free(temp.argv);
        skip:
            {}
        int fd = -1;
        if(filemode == 'r')
            {
                fd = open(filename,O_RDONLY);
                if(fd == -1)
                    printf("Error opening %s\n",filename);
            }
        else if(filemode == 'w')
            {
                fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0744);
                if(fd == -1)
                    {
                        loop:
                        printf("%s already exists->overwrite(y/n):",filename);
                        char ch[3];
                        getstr_alpha_(ch, 3, "");
                        if(ch[0] == 'y' && strlen(ch)==1)
                            fd = open(filename, O_TRUNC | O_WRONLY);
                        else if (ch[0] == 'n')
                            return -1;
                        else
                         goto loop;

                    }
            }
        else
            printf("Invalid filemode\n");

        return fd;
    }


