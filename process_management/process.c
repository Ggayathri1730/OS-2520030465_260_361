#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "process.h"

void create_process(const Student *students, int count)
{
    if (students == NULL || count <= 0)
        return;

    pid_t pid;
    int status;

    printf("\n===== Process Management =====\n");
    printf("Parent process started. PID: %d\n", getpid());
    fflush(stdout);

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }
    else if (pid == 0)
    {
        printf("Child process created.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("\nChild is processing student records:\n");

        for (int i = 0; i < count; i++)
        {
            printf("Processing Student ID: %d, Name: %s\n",
                   students[i].id, students[i].name);
        }

        printf("Child completed processing student records.\n");
        fflush(stdout);
        _exit(0);
    }
    else
    {
        printf("Parent created child with PID: %d\n", pid);

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid failed");
            return;
        }

        if (WIFEXITED(status))
        {
            printf("Child exited with status: %d\n",
                   WEXITSTATUS(status));
        }

        printf("Parent process finished waiting.\n");
    }
}
