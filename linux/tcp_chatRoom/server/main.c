#include "main.h"

typedef enum {
    _Import = 1,
    _Export,
    _Add,
    _Delete,
    _Search,
    _Print_Table,
    _Ext
}state;

int main()
    {
        user_store_hash arr[userCRUD_HASHLEN]={0};
        loop:
        printf("%d)Import contacts\n%d)Export Contacts\n%d)Add/Edit Contact\n%d)Delete Contact\n%d)Search Contact\n%d)Print Contacts\n%d)Exit\n",_Import,_Export,_Add,_Delete,_Search,_Print_Table,_Ext);
        switch(getlong("Option:"))
            {
                case _Add:
                    {
                        printf("Add\n");
                        char name[31];
                        char ph_no[11];
                        add(arr, getstr_num(ph_no, 11, "Number:"), getstr_alpha_(name, 31, "Name:"));
                    }
                    break;
                case _Delete:
                    {
                        printf("Delete\n");
                        char name[31];
                        delete_(arr, getstr_alpha_(name, 31, "Name:"));
                                      
                    }
                    break;
                case _Search:
                    {
                        printf("Search\n");
                        char name[31];
                        search(arr, getstr_alpha_(name, 31, "Name:"));
                                      
                    }
                    break;
                case _Print_Table:
                    print_table(arr);
                    break;
                case _Import:
                    {
                        printf("Import\n");
                        char filename[31];
                        import_(arr, getstr(filename, 31, "Enter filename:"));
                    }
                    break;
                case _Export:
                    {
                        printf("Export\n");
                        char filename[31];
                        export_(arr, getstr(filename, 31, "Enter filename:"));
                    }
                    break;
                case _Ext:
                    return 0;
                default:
                    break;

            }
            
        goto loop;
    }