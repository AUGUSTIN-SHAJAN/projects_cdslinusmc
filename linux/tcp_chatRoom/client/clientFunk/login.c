#include "clientFunk.h"
#include <unistd.h>

server_ack
 login(int sock_fd)
    {
        int byte=0;
        if(1)
            {
                char uname[91];
                char pass[91];
                char code = _LOGIN;
                getstr(uname, 91, "Username:");
                getstr(pass, 91, "Pass:");
                char pass_len = strlen(pass);
                char uname_len = strlen(uname);
                byte = write(sock_fd, &code, 1);
                if(byte!=1) goto err;
                byte = write(sock_fd,(char*)&uname_len,1);
                if(byte!=1) goto err;
                byte = write(sock_fd,uname,uname_len);
                if(byte!=uname_len) goto err;
                byte = write(sock_fd,(char*)&pass_len,1);
                if(byte!=1) goto err;
                byte = write(sock_fd,pass,pass_len);
                if(byte!=pass_len) goto err;
                byte = read(sock_fd, &code, 1);
                if(byte!=1) goto err;
                
                return code;
            }
        else
            {
                err:
                if(byte == 0)
                    {
                        printf("server disconnected\n");
                        close(sock_fd);
                    }
                else if (byte == -1)
                    {
                        printf("Buffer error\n");
                        
                    }
                    
                return _LOGIN_FAIL;
            }
        
    }