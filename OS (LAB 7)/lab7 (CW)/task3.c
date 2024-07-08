#include <unistd.h>

int main(void)
{
    char *binarypath = "/bin/ls";
    char *arg[] = {binarypath, "-lh", "/home", NULL};

    execv(binarypath, arg);
    return 0;
}