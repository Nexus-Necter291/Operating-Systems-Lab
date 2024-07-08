#include <stdio.h>
#include <stdlib.h>

int main()
{
    int counter = 0;

    int pid = fork();

    if (pid == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            counter++;
            printf("Child Process: Counter = %d\n", counter);
            usleep(100000);
        }
        wait(NULL);
    }

    else
    {
        for (int i = 0; i < 10; i++)
        {
            counter++;
            printf("Parent Process: Counter = %d\n", counter);
            usleep(100000);
        }
        wait(NULL);
        printf("Both processes completed.\n");
    }

    return 0;
}
