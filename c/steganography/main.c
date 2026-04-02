#include "main.h"
#include <stdio.h>

int main(int argc,char **argv)
    {
        appData info={.argc=argc,.argv=argv};

        switch(argc)
            {
                case 2:
                    {
                        decode_bmp(info);
                    }
                    break;
                case 3:
                    {
                        encode_bmp(info);
                    }
                    break;
                default:
                    printf("encode\n<bin> <bmp file> <file_to_encode>\n");
                    printf("decode\n<bin> <bmp file>\n");
            }
        
        return 0;
    }