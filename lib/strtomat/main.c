#include "strtomat.h"
#include <stdio.h>

int main()
    {
        char str[100];
        scanf("%[^\n]\n",str);
        char n;
        scanf("%c",&n);
        strmat temp = strtomat(str,n);
        for(int i=0;i<temp.argc;i++)
            {
                printf("%s\n",temp.argv[i]);
            }
        if(temp.argv[temp.argc] == NULL)
            printf("NULL\n");
        return 0;
    }