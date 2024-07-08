#include <stdio.h>
#include <pthread.h>

int global_variable = 0;
int result = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg)
{
    int local_variable = 0;

    pthread_mutex_lock(&mutex);
    global_variable++;
    local_variable = global_variable;
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    result += local_variable;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);
    pthread_create(&thread3, NULL, thread_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("Final value of global_variable: %d\n", global_variable);
    printf("Final value of result: %d\n", result);

    return 0;
}