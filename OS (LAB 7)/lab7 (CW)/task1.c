#include <unistd.h>

int main(void)
{
    char *binarypath = "/bin/ls";
    char *arg1 = "-lh";
    char *arg2 = "/home";

    execl(binarypath, binarypath, arg1, arg2, NULL);
    return 0;
}