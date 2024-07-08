#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int pipefd[2];
    int pid;
    char message[100];

    printf("Enter the message to send from Parent to Child: ");
    fgets(message, sizeof(message), stdin);

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(pipefd[1]);
        char received_message[100];
        read(pipefd[0], received_message, sizeof(received_message));
        printf("Child: I have received this message from parent: %s\n", received_message);
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipefd[0]);
        printf("Parent: I am Parent. I have sent message to the Child.\n");
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}
