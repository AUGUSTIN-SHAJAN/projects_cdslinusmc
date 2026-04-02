#include "main.h"
#include <stddef.h>
#include <unistd.h>

char decode(char *str)
    {
        char alpha = 0;
        for(int i = 7; i >= 0; i--)
            alpha |= ((str[i] & 1) << (7-i));
        return alpha;
    }
status decode_bmp(appData info)
    {
        int bmp_fd = parse_file(info.argv[1], "bmp", 'r');
        if(bmp_fd == -1)
            return FAIL;
        int out_fd = parse_file("out", "", 'w');
        if(out_fd == -1)
            {
                close(bmp_fd);
                return FAIL;
            }
        char buf[64];
        char out_buf[8];
        size_t read_block = 0;
        //parse header and extension
        read_block = read(bmp_fd, buf, 54);
        if(read_block != 54)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                unlink("out");
                close(out_fd);
                return FAIL;
            }
        int fileLen = -1;
        for(size_t i = 0; i < 4 && (read_block = read(bmp_fd, buf, 8)); i++)
            {
                ((char*)&fileLen)[i] = decode(buf);
            }
        if(!read_block)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                unlink("out");
                close(out_fd);
                return FAIL;
            }//read fileLen
        if(fileLen == -1)
            {
                printf("Incomplete File write\n");
            }
        int strln = 0;
        for(size_t i = 0; i < 4 && (read_block = read(bmp_fd, buf, 8)); i++)
            {
                ((char*)&strln)[i] = decode(buf);
            }
        if(!read_block)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                unlink("out");
                close(out_fd);
                return FAIL;
            }//read filename_len
        
        char filename[strln+1];
        filename[strln] = 0;
        int i=0;
        while (i < strln && (read_block = read(bmp_fd, buf, 8)))
            {
                
                filename[i++] = decode(buf);
            }
        if(!read_block)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                unlink("out");
                close(out_fd);
                return FAIL;
            }//read filename
        int xdx = 0;
        while ((read_block = read(bmp_fd, buf, 64)))
            {
                size_t writeCount = read_block/8;
                size_t i;
                for( i = 0; i < writeCount; i++)
                    {
                        if(fileLen != -1 && xdx++ == fileLen)
                            {
                                write(out_fd, out_buf, i);
                                goto jmp;
                            }
                        out_buf[i] = decode(&buf[i*8]);
                    }
                    
                write(out_fd, out_buf, i);
            }
        //rename out file to correct extension
        jmp:
        close(bmp_fd);
        close(out_fd);
     if (rename("out", filename) == 0) 
        {
            printf("%s decoded\n",filename);
        } else {
            printf("rename out to %s\n",filename);
        }
        return SUCCESS;
    }