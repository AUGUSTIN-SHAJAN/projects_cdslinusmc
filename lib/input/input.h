#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
char *getstr(char *str, int strlenPlusOne, char *prompt);
long getlong(char *prompt);
char *getstr_num(char *str, int strlenPlusOne, char *prompt);