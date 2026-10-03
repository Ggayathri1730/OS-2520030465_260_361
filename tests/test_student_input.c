#include <stdio.h>
#include <stdlib.h>
#include "../src/student_input.h"

int main()
{
    int count = 0;

    Student *students = get_student_records(&count);

    if (students == NULL)
    {
        printf("Student input failed.\n");
        return 1;
    }

    printf("\n===== Student Details =====\n");

    for (int i = 0; i < count; i++)
    {
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
    }

    free(students);
    printf("\nMemory released successfully.\n");

    return 0;
}
