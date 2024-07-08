#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    pthread_t tid = pthread_self();

    pid_t pid = getpid();

    printf("Thread ID: %lu, Process ID: %d\n", tid, pid);
    printf("Thread %lu is executing\n", tid);

    return NULL;
}

int main()
{
    pthread_t threads[4];

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}