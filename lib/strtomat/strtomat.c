#include "strtomat.h"
typedef struct node
    {
        char *str;
        struct node *next;
    }node;

typedef struct
    {
        int argc;
        node *head;
    }argcNSLL;

static node *alloc(char *str)
    {
        node *temp = malloc(sizeof(*temp));
        if(temp == NULL)
            return NULL;
        temp->str = str;
        temp->next = NULL;
        return temp; 
    }
static void attach(node **head,node **tail,char *str)
    {
        if(*head == NULL)
            *head = *tail = alloc(str);
        else
            {
                node *temp = alloc(str);
                if(temp == NULL)
                    return;
                (*tail)->next = temp;
                *tail = temp;
            }
    }
static void freee(node *head)
    {
        while(head!=NULL)
            {
                node *temp =head;
                head = head->next;
                free(temp);
            }
    }

static argcNSLL strtoSLL(char *str,char tokcom){
    node *head = NULL;
    node *tail = NULL;
    argcNSLL j={0};

    while(*str == tokcom)
        {
            *str =0;
            str++;
        }
    switch(*str!=0 && *str !=tokcom)
        {
            case 0:
                goto jmp;
            case 1:
                j.argc++;
                attach(&head, &tail, str);
        }
    while(*str)
        {
            if(*str == tokcom)
                {
                    while(*str == tokcom)
                            {
                                *str =0;
                                str++;
                            }
                        switch(*str)
                            {
                                case 0:
                                    goto jmp;
                                default:
                                    j.argc++;
                                    attach(&head, &tail, str);
                            }
                }
            str++;
        }
    jmp:   
    j.head =head;
    return j;
}

strmat strtomat(char *str, char token)
    {
        argcNSLL temp = strtoSLL(str,token);
        strmat out = {0};
        out.argc = temp.argc;
        out.argv = malloc((temp.argc + 1) * sizeof(*out.argv));
        out.argv[temp.argc] = NULL;
        for(int i=0;i<temp.argc;i++)
            {
                out.argv[i] = temp.head->str;
                temp.head = temp.head->next;
            }
        freee(temp.head);
        return out;
    }
