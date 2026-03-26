#include <stdio.h>
#include <stdlib.h>

typedef struct
    {
        int argc;
        char **argv;
    }strmat;

strmat strtomat(char *destructive_str, char token);