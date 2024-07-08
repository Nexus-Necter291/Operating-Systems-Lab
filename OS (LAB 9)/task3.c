#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *job1(void *arg)
{
    printf("Thread 1 is performing job 1\n");
    return NULL;
}

void *job2(void *arg)
{
    printf("Thread 2 is performing job 2\n");
    return NULL;
}

void *job3(void *arg)
{
    printf("Thread 3 is performing job 3\n");
    return NULL;
}

void *job4(void *arg)
{
    printf("Thread 4 is performing job 4\n");
    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3, thread4;

    pthread_create(&thread1, NULL, job1, NULL);
    pthread_create(&thread2, NULL, job2, NULL);
    pthread_create(&thread3, NULL, job3, NULL);
    pthread_create(&thread4, NULL, job4, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    exit(0);
}