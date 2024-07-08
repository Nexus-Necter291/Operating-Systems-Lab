#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Parent PID: %d\n", getpid());
    int pid1, pid2, pid3;

    pid1 = fork();

    if (pid1 == 0)
    {
        printf("First child PID: %d\n", getpid());
    }
    else
    {
        wait(NULL);
        pid2 = fork();

        if (pid2 == 0)
        {
            printf("Second child PID: %d\n", getpid());
        }
        else
        {
            wait(NULL);
            pid3 = fork();

            if (pid3 == 0)
            {
                printf("Third child PID: %d\n", getpid());
            }
            else
            {
                 wait(NULL);
                printf("Parent PID: %d\n", getpid());
            }
        }
    }

    return 0;
}
