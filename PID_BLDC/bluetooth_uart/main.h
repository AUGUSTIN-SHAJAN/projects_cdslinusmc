#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "bluez.h"
#ifndef BLAH
#define BLAH

bdaddr_t get_bdaddr();
int get_rfcomm_channel(bdaddr_t mac_address);
int get_rfcomm_socket(int rfcomm_channel,bdaddr_t mac_address_bluetooth);
#endif