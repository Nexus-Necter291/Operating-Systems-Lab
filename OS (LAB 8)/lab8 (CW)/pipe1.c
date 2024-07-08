#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 

char *message = "This is a message!!!";

int main()
{
    char buf[1024];
    int fd[2];
    pipe(fd);
    if (fork() != 0)
    {
        close(fd[0]);
        write(fd[1], message, strlen(message) + 1);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buf, 1024);
        printf("Read's message is %s\n", buf);
    }
    return 0;
}
