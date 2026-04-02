
#include "../../lib/input/input.h"
#include "../../lib/strtomat/strtomat.h"
#include <string.h>
#include <fcntl.h>


#ifndef PARSE
#define PARSE
int parse_file(char *filename, char *extension, char filemode);
#endif