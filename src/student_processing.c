#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "student_processing.h"

typedef struct
{
    Student *students;
    int count;
    pthread_mutex_t *mutex;
    int *completed_workers;
} ThreadData;

void *marks_worker(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    for (int i = 0; i < data->count; i++)
    {
        float total = 0;

        for (int j = 0; j < 3; j++)
            total += data->students[i].marks[j];

        data->students[i].total = total;
        data->students[i].average = total / 3.0f;
    }

    pthread_mutex_lock(data->mutex);
    (*data->completed_workers)++;
    printf("Marks thread completed.\n");
    pthread_mutex_unlock(data->mutex);

    return NULL;
}

void *attendance_worker(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    for (int i = 0; i < data->count; i++)
    {
        data->students[i].attendance_percentage =
            data->students[i].attended_classes * 100.0f /
            data->students[i].total_classes;
    }

    pthread_mutex_lock(data->mutex);
    (*data->completed_workers)++;
    printf("Attendance thread completed.\n");
    pthread_mutex_unlock(data->mutex);

    return NULL;
}

void process_students_concurrently(Student *students, int count)
{
    if (students == NULL || count <= 0)
    {
        printf("Invalid student records.\n");
        return;
    }

    pthread_t marks_thread, attendance_thread;
    pthread_mutex_t mutex;
    int completed_workers = 0;

    int rc = pthread_mutex_init(&mutex, NULL);
    if (rc != 0)
    {
        fprintf(stderr, "Mutex initialization failed: %s\n",
                strerror(rc));
        return;
    }

    ThreadData data = {students, count, &mutex, &completed_workers};

    printf("\nStarting student processing threads...\n");

    rc = pthread_create(&marks_thread, NULL, marks_worker, &data);
    if (rc != 0)
    {
        fprintf(stderr, "Marks thread creation failed: %s\n",
                strerror(rc));
        pthread_mutex_destroy(&mutex);
        return;
    }

    rc = pthread_create(&attendance_thread, NULL,
                        attendance_worker, &data);
    if (rc != 0)
    {
        fprintf(stderr, "Attendance thread creation failed: %s\n",
                strerror(rc));
        pthread_join(marks_thread, NULL);
        pthread_mutex_destroy(&mutex);
        return;
    }

    pthread_join(marks_thread, NULL);
    pthread_join(attendance_thread, NULL);

    printf("Completed workers: %d\n", completed_workers);
    printf("All student processing completed.\n");

    pthread_mutex_destroy(&mutex);
}
