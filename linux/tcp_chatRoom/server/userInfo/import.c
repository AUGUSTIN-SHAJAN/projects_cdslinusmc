#include "../main.h"

static int parse_line(user_store_hash arr[],char *line)
    {
        strmat temp = strtomat(line, ',');
        
        add(arr, temp.argv[1], temp.argv[0]);
        
        free(temp.argv);
        return 1;
    }
userCRUD import_(user_store_hash arr[], char *filename)
    {
        
        int fd = parse_file(filename,"csv",'r');
        if( fd == -1)
            {
                return FAIL;
            }
        
        char buffer[100]={0};
        int vEOF;
        read(fd,buffer,15);
        if(strcmp(buffer,"uname,password\n"))
            {

                printf("Wrong Format\n");
                printf("Export and check the file\n");
                return FAIL;
            }
         
        int i = 0;
        while ((vEOF = read(fd,&buffer[i],1)))
            {
                if(vEOF == -1)
                    {
                        printf("File IO error\n");
                        close(fd);
                        return FAIL;
                    }
                
                if(buffer[i] == '\n')
                    {
                        buffer[i] = 0;
                        i=-1;
                        if(strlen(buffer)>8)
                            parse_line(arr, buffer);
                        
                    }
                    
                i = (i+1)%100;
                    
            }
        if(strlen(buffer)>8)//8 for strlen(uname) + strlen(password)
            parse_line(arr, buffer);
        return SUCCESS;

    }