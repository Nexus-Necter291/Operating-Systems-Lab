#include <unistd.h>

int main(void)
{
    char *programName = "ls";
    char *arg[] = {programName, "-lh", "/home", NULL};

    execvp(programName, arg);
    return 0;
}