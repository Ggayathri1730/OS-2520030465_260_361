# Multithreaded Linux Application Using POSIX Threads and Mutexes

## Operating Systems and Systems Programming Project

## 1. Project Overview

This project is a multithreaded Linux application developed in C
using POSIX threads, mutex synchronization and process management.

The application accepts student academic and attendance records,
calculates marks and attendance concurrently, and generates a
consolidated report.

It demonstrates operating system concepts including process
creation, thread management, synchronization, dynamic memory
allocation and file handling.

## 2. Objectives

- Develop a C application for Linux.
- Create a child process using fork().
- Manage process completion using waitpid().
- Execute marks and attendance calculations using POSIX threads.
- Use a mutex to protect a shared worker-completion counter.
- Allocate and release memory dynamically.
- Generate a report containing the processed student records.

## 3. Technologies Used

- Operating System: Ubuntu Linux (WSL 2)
- Programming Language: C
- Compiler: GCC
- Build System: GNU Make
- Thread Library: POSIX Threads (pthreads)
- Process Management: fork(), waitpid()
- Synchronization: POSIX Mutex
- File Handling: C standard I/O

## 4. Application Workflow

1. Accept student details from the user.
2. Allocate memory for student records.
3. Create a child process using fork().
4. Display student record information in the child process.
5. Wait for the child process to complete.
6. Create worker threads for marks and attendance calculations.
7. Use a mutex to synchronize access to the shared worker counter.
8. Join the worker threads.
9. Display the calculated student results.
10. Save the report to output/student_report.txt.
11. Release dynamically allocated memory.

## 5. Main Modules

### Student Input
Accepts student IDs, names, subject marks and attendance
details, with input validation.

### Process Management
Uses fork() to create a child process and waitpid() to
wait for its completion.

### Multithreading and Synchronization
Uses two POSIX worker threads:
- Marks calculation
- Attendance calculation

A mutex protects the shared worker-completion counter.

### Memory Management
Uses dynamic memory allocation and releases allocated
memory after processing.

### Report Generation
Writes student marks, averages and attendance details
to output/student_report.txt.

## 6. Project Structure

task_processing_system/
├── src/
│   ├── main.c
│   ├── student.h
│   ├── student_input.c
│   ├── student_input.h
│   ├── student_processing.c
│   ├── student_processing.h
│   ├── memory.c
│   ├── memory.h
│   ├── report.c
│   └── report.h
├── process_management/
│   ├── process.c
│   └── process.h
├── tests/
├── output/
│   └── student_report.txt
├── archive/
├── Makefile
└── README.md

## 7. Compilation

Open the project directory in the Ubuntu terminal:

    cd "$HOME/OS Project/task_processing_system"

Compile the application:

    make

## 8. Execution

Run the application:

    ./task_processing_system

Enter the requested student details when prompted.

## 9. Generated Output

The application generates a student performance report at:

    output/student_report.txt

The report includes:
- Student ID and name
- Subject-wise marks
- Total marks
- Average marks
- Total classes
- Classes attended
- Attendance percentage

## 10. Verified Execution

The application was tested with a sample student record.

Student ID: 101
Name: Gayathri
Subject marks: 85, 90, 88
Total marks: 263
Average: 87.67
Total classes: 100
Classes attended: 92
Attendance: 92%

The child process completed with exit status 0.
Both worker threads completed, the report was saved,
and allocated memory was released.

## 11. Current Scope

The current implementation demonstrates process creation,
thread execution, mutex synchronization, student data
processing, report generation and dynamic memory management.

A separate comparison of synchronized and unsynchronized
execution and experiments with different thread counts
are not included in the verified application workflow.

## 12. Conclusion

The project demonstrates the use of Linux system programming
and POSIX APIs in a practical C application. It integrates
process management, concurrent processing, synchronization,
memory management and file handling into one application.
