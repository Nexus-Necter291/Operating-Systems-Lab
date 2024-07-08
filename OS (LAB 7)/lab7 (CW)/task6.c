#include <unistd.h>

int main(void)
{
    char *binarypath = "/bin/bash";
    // char *arg2 = "echo "Visit $HOSTNAME:$PORT from your browser."";
    char *const args[] = {binarypath,"-c","echo",""};
    execle(binarypath, binarypath, arg1, arg2, NULL, env);
    return 0;
}