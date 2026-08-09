#include "clientFunk/clientFunk.h"
#include "main.h"
#include <stdio.h>
#include <unistd.h>
atomic_int lock = 0;
int sock_fd = -1;
void *worker(void *arg)
{
   char code;
   char byte;
   trip:
   byte = read(sock_fd, &code, 1);
   if(byte<=0)exit(0);
   switch(code)
    {
        case _REC_NA:
            printf("Recevier not availabel\n");
            break;
        case _ONLINE_LIST:
            {
                char sender_len;
                byte = read(sock_fd, &sender_len,1);//read senderlen
                if(byte<=0)exit(0);
                char sender[sender_len + 1];
                byte = read(sock_fd, sender, sender_len);//read sender
                if(byte<=0)exit(0);
                sender[byte]=0;
                printf("%s online\n",sender);
                break;
            }
        case _OFFLINE_LIST:
            {
                char sender_len;
                byte = read(sock_fd, &sender_len,1);//read senderlen
                if(byte<=0)exit(0);
                char sender[sender_len + 1];
                byte = read(sock_fd, sender, sender_len);//read sender
                if(byte<=0)exit(0);
                sender[byte]=0;
                printf("%s offline\n",sender);
                break;
            }
        case _MSG:
            {
                char msg_len,sender_len;
                byte = read(sock_fd, &sender_len,1);//read senderlen
                if(byte<=0)exit(0);
                char sender[sender_len + 1];
                sender[sender_len]=0;
                byte = read(sock_fd, sender, sender_len);//read sender
                if(byte<=0)exit(0);

                byte = read(sock_fd, &msg_len,1);//read msglen
                if(byte<=0)exit(0);
                char msg[msg_len + 1];
                msg[msg_len]=0;
                byte = read(sock_fd, msg, msg_len);//read msg
                if(byte<=0)exit(0);
                printf("%s:%s\n",sender,msg);
                break; 
            }
    }
    goto trip;
    return NULL;
}
int main(int argc, char **argv)
{
    system("clear");
    char *server_ip = argv[1];
    int server_port = 9990;
    int ipv = AF_INET;
    sock_fd = socket(ipv, SOCK_STREAM, 0);

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

int log = 1;

pthread_t thread;
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(
    &attr,
    PTHREAD_CREATE_DETACHED
);

while(log)
    {
        printf("op\n");
        if(login(sock_fd)==_LOGIN_SUCCESS)
            {
                printf("ji\n");
                log=0;
            }
        else
            {
                printf("Wrong Password/username(min length 4)\n");
                printf("Press Enter\n");
                getchar();
                system("clear");
            };        
    }
    
    pthread_create(
    &thread,
    &attr,
    worker,
    NULL
    );
    pthread_attr_destroy(&attr);
    char byte =-1;
    while(1)
        {
            char rn[2]={0};
            char code;
            getstr_num(rn, 2, "1)Broadcast\n2)DM\n3)logout\n");
            char msg_buffer[255];
            switch(rn[0])
                {
                    case '1':
                    code = _BROADCAST;
                    goto skip;
                        break;
                    case '2':
                        code  = _DIRECTMSG;
                        skip:
                        char receiver[255];
                        getstr(receiver, 250, "receiver:");
                        getstr(msg_buffer, 250, "MSG:");
                        char rec_len = strlen(receiver);
                        char msglen = strlen(msg_buffer);
                        byte = write(sock_fd, &code, 1);//code
                        if(byte <= 0) goto err;
                        byte = write(sock_fd, &rec_len, 1);//reclen
                        if(byte <= 0) goto err;
                        byte = write(sock_fd, receiver, rec_len);//rec
                        if(byte <= 0) goto err;
                        byte = write(sock_fd, &msglen, 1);//msglen
                        if(byte <= 0) goto err;
                        byte = write(sock_fd, msg_buffer, msglen);//msg
                        if(byte <= 0) goto err;
                        break;
                    case '3':
                        close(sock_fd);
                        execvp(argv[0], argv);
                        printf("logout error/n");
                        return -1;
                    default:
                        printf("select correct option\n");
                        break;
                }
        }
    if(0)
        {
            err:
            printf("server disconnected\n");
            exit(0);
        }

}