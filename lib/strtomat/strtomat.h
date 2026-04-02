#include <stdio.h>
#include <stdlib.h>

#ifndef STRMATR
#define STRMATR

typedef struct
    {
        int argc;
        char **argv;
    }strmat;

strmat strtomat(char *destructive_str, char token);

#endif