#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "thread_pool.h"

static pthread_t threads[NUM_THREADS];
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker_function(void *arg)
{
    int thread_id = *(int *)arg;

    pthread_mutex_lock(&mutex);

    printf("Thread T%d is processing a task.\n", thread_id);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void start_thread_pool(void)
{
    static int thread_ids[NUM_THREADS];

    printf("\nStarting thread pool with %d threads...\n",
           NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i + 1;

        if (pthread_create(&threads[i],
                           NULL,
                           worker_function,
                           &thread_ids[i]) != 0)
        {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
}

void stop_thread_pool(void)
{
    pthread_mutex_destroy(&mutex);
}
