#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../../../lib/input/input.h"
#include <errno.h>
#include "clientFunk/clientFunk.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdatomic.h>

