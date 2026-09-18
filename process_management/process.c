#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    printf("Parent process started.\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\nChild process created.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("Child is processing tasks...\n");

        for (int i = 1; i <= 5; i++)
        {
            printf("Child processed task %d\n", i);
        }

        printf("Child completed all tasks.\n");

        return 0;
    }
    else
    {
        printf("\nParent created child with PID: %d\n", pid);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("\nParent received child completion.\n");
            printf("Child exited with status: %d\n",
                   WEXITSTATUS(status));
        }

        printf("Parent process finished.\n");
    }

    return 0;
}
