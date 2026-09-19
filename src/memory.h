#ifndef MEMORY_H
#define MEMORY_H

typedef struct
{
    int id;
    char name[100];
} Task;

Task *create_task_array(int size);
Task *resize_task_array(Task *tasks, int new_size);
void free_task_array(Task *tasks);

#endif
