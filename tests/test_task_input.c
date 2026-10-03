#include <stdio.h>
#include <stdlib.h>

#include "../src/task_input.h"

int main()
{
    int task_count;

    Task *tasks = get_user_tasks(&task_count);

    if (tasks == NULL)
    {
        printf("Task input failed.\n");
        return 1;
    }

    printf("\n===== Tasks Entered =====\n");

    for (int i = 0; i < task_count; i++)
    {
        printf("Task %d: %s\n",
               tasks[i].id,
               tasks[i].name);
    }

    free_task_array(tasks);

    printf("\nTasks memory released successfully.\n");

    return 0;
}
