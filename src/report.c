
#include <stdio.h>
#include "report.h"

int save_student_report(const Student *students, int count,
                        const char *filename)
{
    if (students == NULL || count <= 0 || filename == NULL)
    {
        return -1;
    }

    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        perror("Unable to create report");
        return -1;
    }

    fprintf(file, "===== STUDENT PERFORMANCE REPORT =====\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "\nStudent ID: %d\n", students[i].id);
        fprintf(file, "Name: %s\n", students[i].name);

        for (int j = 0; j < 3; j++)
        {
            fprintf(file, "Subject %d Marks: %.2f\n",
                    j + 1, students[i].marks[j]);
        }

        fprintf(file, "Total Marks: %.2f\n", students[i].total);
        fprintf(file, "Average: %.2f\n", students[i].average);
        fprintf(file, "Total Classes: %d\n", students[i].total_classes);
        fprintf(file, "Classes Attended: %d\n",
                students[i].attended_classes);
        fprintf(file, "Attendance: %.2f%%\n",
                students[i].attendance_percentage);
        fprintf(file, "-----------------------------------\n");
    }

    if (fclose(file) != 0)
    {
        perror("Error closing report");
        return -1;
    }

    printf("Student report saved successfully.\n");
    return 0;
}
