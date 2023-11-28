#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define namepipe "./namepipe"

int namep;

int main()
{
    int n, fd;
    char msg[100];
    int pipeline[2];

    namep = open(namepipe, O_RDWR);

    fd = open("serverlog.txt", O_CREAT | O_APPEND | O_WRONLY, 0666);
    if (fd < 0) {
        printf("\n로그파일 생성 실패\n");
    }
    printf("\n로그파일 생성\n");

    while (1) {
        if (read(namep, msg, sizeof(msg)) > 0) {
            msg[strlen(msg)] = '\n';
            write(fd, msg, strlen(msg));
            memset(msg, 0, sizeof(msg));
        }
    }

    return 1;
}
