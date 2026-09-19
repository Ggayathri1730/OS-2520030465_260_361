#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

Task *create_task_array(int size)
{
    Task *tasks = malloc(size * sizeof(Task));

    if (tasks == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    return tasks;
}

Task *resize_task_array(Task *tasks, int new_size)
{
    Task *temp = realloc(tasks, new_size * sizeof(Task));

    if (temp == NULL)
    {
        perror("realloc failed");
        free(tasks);
        exit(EXIT_FAILURE);
    }

    return temp;
}

void free_task_array(Task *tasks)
{
    free(tasks);
}
