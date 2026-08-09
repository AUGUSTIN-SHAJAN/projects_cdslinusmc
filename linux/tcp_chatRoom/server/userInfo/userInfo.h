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
        struct user_personal_info *left;
        struct user_personal_info *right;
        int fd;
    }user_personal_info;

typedef struct user_store_hash
    {
        user_personal_info *hash_node;
    }user_store_hash;

typedef enum {
    SUCCESS,
    FAIL,
    PASSWRONG
}userCRUD;



userCRUD import_(user_store_hash arr[], char *filename);
userCRUD export_(user_store_hash arr[], char *filename);

user_personal_info *add(user_store_hash arr[],char *password, char *uname,int fd);
int search(user_store_hash arr[], char *uname);
userCRUD delete_(user_store_hash arr[],char *uname);
userCRUD print_table(user_store_hash arr[]);
#endif