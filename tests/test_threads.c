#include <stdio.h>
#include "../src/thread_pool.h"

int main(void)
{
    printf("Starting POSIX thread pool test...\n");

    start_thread_pool();

    printf("Thread pool test completed successfully.\n");

    stop_thread_pool();

    return 0;
}
