#include "../../lib/parse_file/parse_file.h"

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
typedef enum
    {
        SUCCESS = 1,
        FAIL
    }status;

typedef struct
    {
        int argc;
        char **argv;
    }appData;

char *encode(char *str, char alpha);
char decode(char *str);

status decode_bmp(appData info);
status encode_bmp(appData info);

