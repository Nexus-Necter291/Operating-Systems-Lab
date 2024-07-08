#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_thread_info(void *arg)
{
    int thread_number = *((int *)arg);
    pthread_t thread_id = pthread_self();
    printf("Hello, I am thread %d, my ID is %lu\n", thread_number, thread_id);
    return NULL;
}

int main()
{
    int num_threads;
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    int thread_args[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        thread_args[i] = i + 1;
        pthread_create(&threads[i], NULL, print_thread_info, &thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    exit(0);
}