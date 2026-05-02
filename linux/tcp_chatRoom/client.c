#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include "/home/neg/projects/lib/input/input.h"
int server_port = 9990;


int main(int argc, char **argv)
{
    char *server_ip = argv[1];
    int server_port = 9990;
    int ipv = AF_INET;
    int sock_fd = socket(ipv, SOCK_STREAM, 0);

    if(sock_fd == -1)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));

    client.sin_family = ipv;
    client.sin_port = htons(server_port);

   switch(inet_pton(ipv, server_ip, &client.sin_addr))
    {
        case 1:
            break;

        case 0:
            printf("Invalid IPv4 address\n");
            return -1;

        case -1:
            perror("inet_pton");
            return -1;
    }

    if(connect(sock_fd, (struct sockaddr *)&client, sizeof(client)))
        {
            perror("connect");
            return -1;
        }
    char buffer[91];
    while(1)
        {
            getstr(buffer, 91, "Enter:");
            write(sock_fd, buffer, strlen(buffer));
        }
}