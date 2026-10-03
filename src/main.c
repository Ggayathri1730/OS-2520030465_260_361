#include <stdio.h>
#include <stdlib.h>

#include "../src/student_input.h"
#include "../src/student_processing.h"
#include "../src/report.h"
#include "../process_management/process.h"

int main(void)
{
    int count = 0;

    Student *students = get_student_records(&count);

    if (students == NULL)
    {
        printf("Student input failed.\n");
        return 1;
    }

    create_process(students, count);

    process_students_concurrently(students, count);

    printf("\n===== Student Results =====\n");

    for (int i = 0; i < count; i++)
    {
        printf("\nStudent ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Total Marks: %.2f\n", students[i].total);
        printf("Average: %.2f\n", students[i].average);
        printf("Attendance: %.2f%%\n",
               students[i].attendance_percentage);
    }


      if (save_student_report(students, count,
                            "output/student_report.txt") == 0)
    {
        printf("Report saved in output/student_report.txt\n");
    }
    else
    {
        printf("Failed to save report.\n");
    }

    free(students);
    printf("\nMemory released successfully.\n");

    return 0;
}
