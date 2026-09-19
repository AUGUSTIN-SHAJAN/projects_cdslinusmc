#include "bluez.h"
#include "main.h"

int main()
    {
       	printf("run bluetoothctl and pair with hc-05/hc-06\n");
	    bdaddr_t mac_address_bluetooth = get_bdaddr();
        if(bacmp(BDADDR_ANY, &mac_address_bluetooth) == 0)
            goto exit;
        int rfcomm_channel = get_rfcomm_channel(mac_address_bluetooth);
        if(rfcomm_channel <= 0)
            goto exit;
        
        int rf_sock_fd = get_rfcomm_socket(rfcomm_channel, mac_address_bluetooth);
        if (rf_sock_fd < 0)
            goto exit;
        while(1);
        exit:
        return 0;
    }
