#include <unistd.h>

int main(void)
{
    char *binarypath = "/bin/bash";
    char *arg1 = "-c";
    char *arg2 = "echo ";
    // char *arg2 = "echo "Visit $HOSTNAME:$PORT from your browser."";
    char *const env[] = {"$HOSTNAME=www.linuxhint.com", "PORT=8080", NULL};
    execle(binarypath, binarypath, arg1, arg2, NULL, env);
    return 0;
}