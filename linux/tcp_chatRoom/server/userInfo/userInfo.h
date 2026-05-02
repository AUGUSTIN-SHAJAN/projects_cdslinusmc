#ifndef USERINFO
#define USERINFO

#include "../../../../lib/input/input.h"
#include "../../../../lib/strtomat/strtomat.h"
#include "../../../../lib/parse_file/parse_file.h"
#include <string.h>
#include <fcntl.h>

#define userCRUD_HASHLEN 27

typedef struct user_personal_info
    {
        char *password;
        char *uname;
        long ph_num;
        char *ip;
        int port;
        struct user_personal_info *left;
        struct user_personal_info *right;
    }user_personal_info;

typedef struct user_store_hash
    {
        user_personal_info *hash_node;
    }user_store_hash;

typedef enum {
    SUCCESS,
    FAIL,
}userCRUD;



userCRUD import_(user_store_hash arr[], char *filename);
userCRUD export_(user_store_hash arr[], char *filename);

userCRUD add(user_store_hash arr[],char *password, char *uname);
userCRUD search(user_store_hash arr[], char *uname);
userCRUD delete_(user_store_hash arr[],char *uname);
userCRUD print_table(user_store_hash arr[]);
#endif