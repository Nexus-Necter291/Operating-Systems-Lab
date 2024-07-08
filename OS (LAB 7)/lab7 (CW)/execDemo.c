#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *args[] = {"./exec", NULL};
    execvp(args[0], args);
    puts("Ending....");
    return 0;
}