#include <stdio.h>
#include <stdlib.h>

typedef struct
    {
        int argc;
        char **argv;
    }strmat;

strmat strtomat(char *str, char token);