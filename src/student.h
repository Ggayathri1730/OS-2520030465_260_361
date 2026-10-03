#ifndef STUDENT_H
#define STUDENT_H

typedef struct
{
    int id;
    char name[100];

    float marks[3];
    float total;
    float average;

    int total_classes;
    int attended_classes;
    float attendance_percentage;

} Student;

#endif
