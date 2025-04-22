#include "../include/philo.h"

pthread_mutex_t mutex;

void *routine1(void *arg)
{
    int x;
    int *result;

    x = *(int *)arg;
    // free(arg);
    result = malloc(sizeof(int));
    if (!result)
    {
        printf("Error allocating memory for result\n");
        return (NULL);
    }
    pthread_mutex_lock(&mutex);
    x++;
    pthread_mutex_unlock(&mutex);
    *result = x;
    return ((void *) result);
}

int main(int argc, char **argv)
{
    (void) argv;

    if (!(argc >= 1))
    {
        printf("Error: Type something\n");
        return (1);
    }
    pthread_t *test_thread;
    int i;
    int *result;
    int *a;

    test_thread = malloc(sizeof(pthread_t) * PHILOS);
    if (test_thread == NULL)
    {
        printf("Error allocating memory for threads\n");
        return (1);
    }
    pthread_mutex_init(&mutex, NULL);
    i = 0;
    while (i < PHILOS)
    {
        a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&test_thread[i], NULL, &routine1, &args) != 0)
        {
            printf("Error creating thread %d\n", i);
            // free(a);
            // free(test_thread);
            pthread_mutex_destroy(&mutex);
            return (1);
        }
        printf("Thread %d created\n", i);
        i++;
    }
    i = 0;
    while (i < PHILOS)
    {
        if (pthread_join(test_thread[i], (void **) &result) != 0)
        {
            printf("Error joining thread %d\n", i);
            return (1);
        }
        printf("Thread %d joined\n", i);
        i++;
    }

    printf("Final value of result: %d\n", *result);
    free(result);

    return (0);
}
