#include <stdio.h>
#include <string.h>

#include "task_input.h"

Task *get_user_tasks(int *task_count)
{
    printf("\n===== Task Input =====\n");

    printf("Enter number of tasks: ");
    scanf("%d", task_count);

    if (*task_count <= 0)
    {
        printf("Invalid number of tasks.\n");
        return NULL;
    }

    Task *tasks = create_task_array(*task_count);

    for (int i = 0; i < *task_count; i++)
    {
        tasks[i].id = i + 1;

        printf("Enter Task %d: ", i + 1);

        scanf(" %[^\n]", tasks[i].name);
    }

    return tasks;
}
