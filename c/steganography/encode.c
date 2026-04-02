#include "main.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>


char *encode(char *str, char alpha)
    {
        for(int i = 7; i >= 0; i--)
            str[i] = (str[i] & ~1) | (alpha & (1 << (8-i-1))) >> (7-i);
        return str;
    }



status encode_bmp(appData info)
    {

        int bmp_fd = parse_file(info.argv[1], "bmp", 'r');
        if(bmp_fd == -1)
            return FAIL;
        int in_fd = parse_file(info.argv[2],"",'r');
        if(in_fd == -1)
            {
                close(bmp_fd);
                return FAIL;
            }
            
        int out_fd = parse_file("encode.bmp", "", 'w');
        if(out_fd == -1)
            {
                close(bmp_fd);
                close(in_fd);
                return FAIL;
            }
        char bmp_buffer[64];
        char in_buffer[8];
        size_t read_block = 0 ;
        read_block = read(bmp_fd,bmp_buffer,54);
        if(!read_block)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                close(in_fd);
                close(out_fd);
                return FAIL;
            }
        write(out_fd, bmp_buffer, 54);//write header
        int file_len = -1;
        for(size_t i = 0; i < 4 && (read_block = read(bmp_fd, bmp_buffer, 8)); i++)
            {
                write(out_fd, encode(bmp_buffer, ((char*)&file_len)[i]), 8);
            }
        if(!read_block)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                close(in_fd);
                close(out_fd);
                return FAIL;
            }//write file_len
        int file_strlen = strlen(info.argv[2]);
        for(size_t i = 0; i < 4 && (read_block = read(bmp_fd, bmp_buffer, 8)); i++)
            {
                write(out_fd, encode(bmp_buffer, ((char*)&file_strlen)[i]), 8);
            }
        if(!read_block)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                close(in_fd);
                close(out_fd);
                return FAIL;
            }//write filename_len
        for(size_t i = 0; i < strlen(info.argv[2]) && (read_block = read(bmp_fd, bmp_buffer, 8)); i++)
            {
                write(out_fd, encode(bmp_buffer, info.argv[2][i]), 8);
            }
        if(!read_block)
            {
                printf("%s corrupted\n",info.argv[1]);
                close(bmp_fd);
                close(in_fd);
                close(out_fd);
                return FAIL;
            }//write file_name
        size_t in_var = 0;
        file_len = 0;
        while((read_block = read(bmp_fd, bmp_buffer, 64)) && (in_var = read(in_fd, in_buffer, read_block/8)))
            {
                for(size_t i = 0; i < in_var; i++)
                    {
                        file_len++;
                        encode(&bmp_buffer[i*8], in_buffer[i]);
                    }
                    

                write(out_fd,bmp_buffer,read_block);
                read_block = 0;
            }//write file
        if(read_block)
            {
                do
                    {
                        write(out_fd,bmp_buffer,read_block);
                    }while((read_block = read(bmp_fd, bmp_buffer, 64)));
                lseek(out_fd, 54, SEEK_SET);
                lseek(bmp_fd, 54, SEEK_SET);
                for(size_t i = 0; i < 4 && (read_block = read(bmp_fd, bmp_buffer, 8)); i++)
                    {
                        write(out_fd, encode(bmp_buffer, ((char*)&file_len)[i]), 8);
                    }
                
            }
        else if(in_var)
            {
                printf("incomplete file encoding %s file size is low\n",info.argv[1]);
            }
        printf("%d bytes encoded\n",file_len);
        close(bmp_fd);
        close(in_fd);
        close(out_fd);
        return SUCCESS;
    }