#include "input.h"

char *getstr(char *str, int strlenPlusOne, char *prompt)
    {
        char *hold=str;
        struct termios old, new;
        // get current terminal settings
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        // disable canonical mode and echo
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);

        printf("%s",prompt);
        for(int i = 0; i < strlenPlusOne - 1; i++)  
            {
                skip:
                str[i] = getchar();
                if(str[i] == '\n')
                    {
                        str[i] = 0;
                        printf("\n");
                        goto jmp;
                    }
                else if(str[i] == 8 || str[i] == 127)
                    {
                        if(i>0)
                            {
                                i--;
                                printf("\b \b");
                                
                            }
                            goto skip;
                        
                    }
                else
                    {
                        printf("%c",str[i]);
                    }
                
            }
        str[strlenPlusOne - 1] = 0;
        printf("\n");
        jmp:
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return hold;
    }

long getlong(char *prompt)
    {
        struct termios old, new;
        // get current terminal settings
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        // disable canonical mode and echo
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);


        char str[21];
        str[20]=0;
        printf("%s",prompt);
        for(int i=0;i<20;i++)
            {
                skip:
                str[i] = getchar();
                if(str[i] == '\n')
                    {
                        str[i] = 0;
                        printf("\n");
                        goto jmp;
                    }
                else if(str[i] == 8 || str[i] == 127)
                    {
                        if(i>0)
                            {
                                i--;
                                printf("\b \b");
                                
                            }
                            goto skip;
                        
                    }
                else if(str[i] >= '0' && str[i] <= '9')
                    {
                        printf("%c",str[i]);
                    }
                else if(i==0 && (str[i] == '-' || str[i] == '+'))
                    {
                        printf("%c",str[i]);
                    }
                else
                    goto skip;
                    
            }
        printf("%c",'\n');
        jmp:
        tcsetattr(STDIN_FILENO, TCSANOW, &old); 
        char *temp;
        return strtol(str, &temp,10);
    }

char *getstr_num(char *str, int strlenPlusOne, char *prompt)
    {
        char *hold=str;
        struct termios old, new;
        // get current terminal settings
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        // disable canonical mode and echo
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);

        printf("%s",prompt);
        for(int i = 0; i < strlenPlusOne - 1; i++)  
            {
                skip:
                str[i] = getchar();
                if(str[i] == '\n')
                    {
                        str[i] = 0;
                        printf("\n");
                        goto jmp;
                    }
                else if(str[i] == 8 || str[i] == 127)
                    {
                        if(i>0)
                            {
                                i--;
                                printf("\b \b");
                                
                            }
                            goto skip;
                        
                    }
                else if(str[i] >= '0' && str[i] <= '9')
                    {
                        printf("%c",str[i]);
                    }
                else if(i==0 && (str[i] == '-' || str[i] == '+'))
                    {
                        printf("%c",str[i]);
                    }
                else
                    goto skip;
                    
            }
        str[strlenPlusOne - 1] = 0;
        printf("\n");
        jmp:
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return hold;
    }

char *getstr_alpha_(char *str, int strlenPlusOne, char *prompt)
    {
        char *hold=str;
        struct termios old, new;
        // get current terminal settings
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        // disable canonical mode and echo
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);

        printf("%s",prompt);
        for(int i = 0; i < strlenPlusOne - 1; i++)  
            {
                skip:
                str[i] = getchar();
                if(str[i] == '\n')
                    {
                        str[i] = 0;
                        printf("\n");
                        goto jmp;
                    }
                else if(str[i] == 8 || str[i] == 127)
                    {
                        if(i>0)
                            {
                                i--;
                                printf("\b \b");
                                
                            }
                            goto skip;
                        
                    }
                else if(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z'))
                    {
                        printf("%c",str[i]);
                    }
                else
                    goto skip;
                    
            }
        str[strlenPlusOne - 1] = 0;
        printf("\n");
        jmp:
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return hold;
    }