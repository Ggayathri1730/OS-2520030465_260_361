#include <stdio.h>
#include "../src/memory.h"

int main()
{
    int size = 3;

    printf("Creating memory for %d tasks...\n", size);

    Task *tasks = create_task_array(size);

    for (int i = 0; i < size; i++)
    {
        tasks[i].id = i + 1;

        snprintf(tasks[i].name,
                 sizeof(tasks[i].name),
                 "TASK %d",
                 i + 1);
    }

    printf("\nInitial tasks:\n");

    for (int i = 0; i < size; i++)
    {
        printf("ID: %d | %s\n",
               tasks[i].id,
               tasks[i].name);
    }

    printf("\nIncreasing memory from 3 to 5 tasks...\n");

    size = 5;

    tasks = resize_task_array(tasks, size);

    for (int i = 3; i < size; i++)
    {
        tasks[i].id = i + 1;

        snprintf(tasks[i].name,
                 sizeof(tasks[i].name),
                 "TASK %d",
                 i + 1);
    }

    printf("\nAfter realloc:\n");

    for (int i = 0; i < size; i++)
    {
        printf("ID: %d | %s\n",
               tasks[i].id,
               tasks[i].name);
    }

    free_task_array(tasks);

    printf("\nMemory released successfully.\n");

    return 0;
}
