#include "../userInfo/userInfo.h"

#ifndef FNK
#define FNK
typedef enum
    {
        _LOGIN,
        _BROADCAST,
        _DIRECTMSG,
        
    }client_req;

typedef enum
    {
        _ONLINE_LIST,
        _OFFLINE_LIST,
        _MSG,
        _LOGIN_FAIL,
        _LOGIN_SUCCESS,
        _REC_NA
    }server_ack;
user_personal_info *login(int fd, user_store_hash online[], user_store_hash users[]);
int directmsg(int rec_fd, char *sender_name,char *msg);
userCRUD broadcast(user_store_hash online[],char *sender_name,char *msg);
userCRUD list(user_store_hash online[],char *sender_name, char code);
#endif