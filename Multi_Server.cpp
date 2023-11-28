// #include <iostream>
#include <stdio.h>
#include <signal.h>
#include<sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t pt[2];
pid_t pid;
int client_socket;
int cla_number;

void* recieve_s(void* soc)
{
    int* socket = (int*)soc;
    char msg[100];
    while (1)
    {
        if (read(*socket, msg, sizeof(msg)) > 0)
        {
            printf("\n%s (서버송신)\n", msg);
            if (strcmp("서버종료", msg) == 0) {
                exit(0);
            }
        }
    }
}

void* send_s(void* soc)
{
    int* socket = (int*)soc;
    char msg[100];
    while (1)
    {
        printf("> %d클라입력 : ", client_socket);
        scanf("%s", msg);
        write(*socket, msg, sizeof(msg));
    }
}

int main()
{
    int port, client_len, server_socket, status;
    char msg[100];
    struct sockaddr_in server_add, client_add;

    port = 5000;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = htonl(INADDR_ANY);
    server_add.sin_port = htons((unsigned short)port);

    while (1) {
        status = connect(client_socket, (const struct sockaddr*)&server_add, sizeof(server_add));
        if (status != -1) break;
    }

    pthread_create(&pt[0], NULL, recieve_s, (void*)&client_socket);
    pthread_create(&pt[1], NULL, send_s, (void*)&client_socket);

    pthread_join(pt[0], (void**)&status);

    return 0;
}