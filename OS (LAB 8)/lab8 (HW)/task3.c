#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "fifo"

int main()
{
    int fd;
    char message[256];

    mkfifo(FIFO_FILE, 0666);
    fd = open("fifo", 2);
    if (fd == -1)
    {
        perror("Error opening FIFO");
        exit(EXIT_FAILURE);
    }
    if (fork() == 0)
    {
        while (1)
        {
            read(fd, message, sizeof(message));
            printf("Received: %s", message);
        }
    }
    else
    {
        while (1)
        {
            fgets(message, sizeof(message), stdin);
            write(fd, message, strlen(message) + 1);
        }
    }
    close(fd);
    return 0;
}
