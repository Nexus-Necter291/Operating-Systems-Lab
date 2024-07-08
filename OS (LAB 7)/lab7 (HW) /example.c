#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    printf("Before exec(), this is example.c\n");

    char *args[] = {"./hello", NULL};
    execvp(args[0], args);

    perror("execvp");
    return 1;
}
