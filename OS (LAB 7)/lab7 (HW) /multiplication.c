#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    printf("Before exec(), this is multiplication.c\n");

    char *args[] = {"./addition", NULL};
    execvp(args[0], args);
    perror("execvp");
    return 1;
}
