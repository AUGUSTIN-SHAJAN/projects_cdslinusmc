#include "../../lib/input/input.h"
#include "../../lib/strtomat/strtomat.h"
#include <string.h>
typedef enum {
    _Import,
    _Export,
    _Add,
    _Delete,
    _Edit,
    _Search,
    _Print_Table,
    _Ext
}state;
typedef struct personal_info
    {
        long number;
        char *name;
        struct personal_info *left;
        struct personal_info *right;
        struct personal_info *prev;
    }personal_info;

typedef struct hash
    {
        personal_info *hash_node;
    }hash;

typedef enum {
    Add_SUCCESS,
    Add_FAIL,
}status;



status import_(hash arr[], char *filename);
status export_(hash arr[], char *filename);

status add(hash arr[],char *ph_num, char *name);


status print_table(hash arr[]);