#include "main.h"

int main()
    {
        hash arr[9]={0};
        loop:
        system("clear");
        printf("%d)Import contacts\n%d)Export Contacts\n%d)Add Contact\n%d)Delete Contact\n%d)Edit Contact\n%d)Search Contact\n%d)Print Contacts\n%d)Exit\n",_Import,_Export,_Add,_Delete,_Edit,_Search,_Print_Table,_Ext);
        switch(getlong("Option:"))
            {
                case _Add:
                    {
                        char name[31];
                        char ph_no[11];
                        add(arr, getstr_num(ph_no, 11, "Number:"), getstr(name, 31, "Name:"));
                    }
                    break;
                case _Delete:
                    break;
                case _Edit:
                    break;
                case _Search:
                    break;
                case _Print_Table:
                    print_table(arr);
                    break;
                case _Import:
                    break;
                case _Export:

                    break;
                case _Ext:
                    return 0;
                default:
                    break;

            }
            
        goto loop;
    }