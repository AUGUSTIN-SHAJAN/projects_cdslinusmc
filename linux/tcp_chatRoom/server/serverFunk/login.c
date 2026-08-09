#include "serverFunk.h"

user_personal_info *login(int fd, user_store_hash online[], user_store_hash users[])
    {
        char uname_len,pass_len;
        int byte;
        byte = read(fd, (char*)&uname_len, 1);//read strlen_uname
        if(byte < 1)
            {
                looper:
                printf("connection issue\n");
                return NULL;
            }
        char uname[uname_len + 1];
        byte = read(fd,uname,uname_len);//read unamee
        if(byte < 1)
            goto looper;
        uname[byte]=0;
        byte = read(fd, (char*)&pass_len, 1);//read passlen
        if(byte < 1)
            goto looper;
        char pass[pass_len + 1];
        byte = read(fd,pass,pass_len);///read pass
        if(byte < 1)
            goto looper;
        pass[byte]=0;
        printf("%s->%s\n",pass,uname);
        user_personal_info *temp = add(users,pass,uname,fd);
        if(temp == NULL)
            {
                printf("Wrong Password\n");//------------------------------------->to client
                return NULL;
            }//for userDB

        user_personal_info *temp1 = add(online,pass,uname,fd);
        if(temp1 == NULL)
            {
                printf("Space not available to add user to online DB\n");//------------------------------------->to client
                return NULL;
            }
        return temp1;
    }