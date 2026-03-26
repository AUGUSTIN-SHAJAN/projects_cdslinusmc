#include "main.h"

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
        int fd = open(filename, O_RDONLY);
            {
                printf("%s couldnt be opened\nMost likely it doesnt exist.\n",filename);
            }
        return fd;
    }
static int parse_line(hash arr[],char *line)
    {
        strmat temp = strtomat(line, ',');
        
        add_edit(arr, temp.argv[1], temp.argv[0]);
        
        free(temp.argv);
        return 1;
    }
status import_(hash arr[], char *filename)
    {
        
        int fd = parse_file(filename);
        if( fd == -1)
            {
                printf("Press Enter to exit\n");
                getchar();
                return Add_FAIL;
            }
        
        char buffer[100]={0};
        int vEOF;
        read(fd,buffer,12);
        if(strcmp(buffer,"Name,Number\n"))
            {

                printf("Wrong Format\n");
                printf("Export and check the file\n");
                printf("Press Enter to exit\n");
                getchar();
                return Add_FAIL;
            }
         
        int i = 0;
        while ((vEOF = read(fd,&buffer[i],1)))
            {
                if(vEOF == -1)
                    {
                        printf("File IO error\n");
                        close(fd);
                        printf("Press Enter to exit\n");
                        getchar();
                        return Add_FAIL;
                    }
                
                if(buffer[i] == '\n')
                    {
                        buffer[i] = 0;
                        i=-1;
                        if(strlen(buffer)>10)
                            parse_line(arr, buffer);
                        
                    }
                    
                i = (i+1)%100;
                    
            }
        if(strlen(buffer)>10)//10 for digits
            parse_line(arr, buffer);
        return Add_SUCCESS;

    }