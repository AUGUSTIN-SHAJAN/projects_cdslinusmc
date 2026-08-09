#include "main.h"

bdaddr_t get_bdaddr()
    {
        bdaddr_t bl_addr = {0};
        int hci_adapter_id = hci_get_route(NULL);//get_adapter_id
        if(hci_adapter_id < 0)
            {
                perror("hci_get_route");
                printf("Turn On Bluetooth\n");
                return bl_addr;
            }
        int hci_adapter_sock_fd = hci_open_dev(hci_adapter_id);//open socket to hci_adapter;
        if(hci_adapter_sock_fd < 0)
            {
                perror("hci_open_dev");
                return bl_addr;
            }
        inquiry_info *ii = NULL;
        int searching_time = 10;//10*1.28 seconds
        int max_devices = 20;
        printf("searching...\n");
        int devices = hci_inquiry(hci_adapter_id, searching_time, max_devices, NULL, &ii, IREQ_CACHE_FLUSH);//discover devices
        if(devices < 0)
            perror("hci_inquiry");
        if(devices < 1)
            {
                printf("No Devices Found\n");
                goto hci_cleanup;
            }
        printf("Devices Found\n");
        for(int i = 0; i < devices; i++)//loop through instances
            {
                char addr[19];
                ba2str(&ii[i].bdaddr, addr);//convert addr to string
                printf("Device %d: %s ",i + 1,addr);

                char name[248]={0};
                int name_service_check = hci_read_remote_name(hci_adapter_sock_fd, &ii[i].bdaddr, sizeof(name), name, 0);//get name
                if(name_service_check < 0)  
                    {strcpy(name, "unknown");}
                printf("%s\n",name);
            }
        loop:
        printf("Enter the number of device to connnect to:");
        int opt = 0;

        while(scanf("%d",&opt) != 1)
            {
                while(getchar() != '\n');
            }
        if(opt < 1 || opt > devices)
            goto loop;
        bl_addr = ii[opt-1].bdaddr;
        hci_cleanup:
        free(ii);
        hci_close_dev(hci_adapter_sock_fd);
        return bl_addr;
    }