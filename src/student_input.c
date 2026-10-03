
#include <stdio.h>
#include <stdlib.h>

#include "student_input.h"

Student *get_student_records(int *count)
{
    if (count == NULL)
        return NULL;

    *count = 0;

    printf("\n===== Student Record Input =====\n");
    printf("Enter number of students: ");

    if (scanf("%d", count) != 1 || *count <= 0 || *count > 100)
    {
        printf("Invalid number of students.\n");
        return NULL;
    }

    Student *students = malloc(*count * sizeof(Student));

    if (students == NULL)
    {
        perror("Memory allocation failed");
        *count = 0;
        return NULL;
    }

    for (int i = 0; i < *count; i++)
    {
        printf("\nEnter details for Student %d\n", i + 1);

        printf("Enter student ID: ");
        if (scanf("%d", &students[i].id) != 1)
            goto input_error;

        printf("Enter student name: ");
        if (scanf(" %99[^\n]", students[i].name) != 1)
            goto input_error;

        for (int j = 0; j < 3; j++)
        {
            printf("Enter marks for Subject %d: ", j + 1);
            if (scanf("%f", &students[i].marks[j]) != 1 ||
                students[i].marks[j] < 0 ||
                students[i].marks[j] > 100)
                goto input_error;
        }

        printf("Enter total classes: ");
        if (scanf("%d", &students[i].total_classes) != 1 ||
            students[i].total_classes <= 0)
            goto input_error;

        printf("Enter classes attended: ");
        if (scanf("%d", &students[i].attended_classes) != 1 ||
            students[i].attended_classes < 0 ||
            students[i].attended_classes > students[i].total_classes)
            goto input_error;

        students[i].total = 0;
        students[i].average = 0;
        students[i].attendance_percentage = 0;
    }

    return students;

input_error:
    printf("Invalid input. Please enter valid values.\n");
    free(students);
    *count = 0;
    return NULL;
}
