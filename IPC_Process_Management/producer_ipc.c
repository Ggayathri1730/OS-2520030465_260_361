/*
 * producer_ipc.c
 *
 * INTER-PROCESS COMMUNICATION PART
 * ---------------------------------
 * This file implements the "Parent -> fork() -> Producer" side of the
 * project diagram:
 *
 *      input.txt
 *          |
 *          v
 *       PARENT
 *          |
 *        fork()
 *        /     \
 *   PRODUCER   WORKER   <-- Worker side (thread pool + mutex) is a
 *      |          ^         teammate's part. Below, the parent process
 *      |  PIPE    |         acts only as a receiving stub to prove the
 *      +--write()-+         pipe works end-to-end.
 *
 * Responsibilities covered here (CO1 + CO2 + CO3):
 *   - fork()                : create a child process (the Producer)
 *   - pipe()                : set up an IPC channel between the two processes
 *   - write() / read()      : send task data from Producer to the other side
 *   - wait()                : parent waits for the Producer child to finish
 *
 * NOTE FOR THE TEAM:
 *   The block marked "WORKER-STUB" below is a placeholder. In the final
 *   integrated version, replace that block with the call into the POSIX
 *   thread pool (pthread_create() + mutex-protected shared queue) that
 *   the other members are building. Everything up to "received a task
 *   string from the pipe" is already working and ready to hand off.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define INPUT_FILE  "input.txt"

int main(void) {
    int pipefd[2];   /* pipefd[0] = read end, pipefd[1] = write end */
    pid_t pid;

    /* Pipe must be created BEFORE fork() so both processes inherit
     * the same pair of file descriptors. */
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);

    } else if (pid == 0) {
        /* ---------------- CHILD PROCESS = PRODUCER ---------------- */
        close(pipefd[0]);   /* Producer only writes; close unused read end */

        FILE *input = fopen(INPUT_FILE, "r");
        if (input == NULL) {
            perror("[PRODUCER] could not open input.txt");
            exit(EXIT_FAILURE);
        }

        printf("[PRODUCER] (pid=%d) reading tasks from %s and sending over the pipe...\n",
               getpid(), INPUT_FILE);

        char line[BUFFER_SIZE];
        while (fgets(line, sizeof(line), input) != NULL) {
            line[strcspn(line, "\n")] = '\0';   /* strip trailing newline */
            if (strlen(line) == 0) {
                continue;
            }

            /* +1 to include the null terminator, so the reader gets a
             * ready-to-use C string on the other end. */
            if (write(pipefd[1], line, strlen(line) + 1) == -1) {
                perror("[PRODUCER] write failed");
                break;
            }

            printf("[PRODUCER] sent: %s\n", line);
            usleep(150000);   /* small delay, purely so the demo output
                                 is readable step by step */
        }

        fclose(input);
        close(pipefd[1]);    /* signal EOF to the reader */
        printf("[PRODUCER] all tasks sent. exiting.\n");
        exit(EXIT_SUCCESS);

    } else {
        /* ---------------- PARENT PROCESS ---------------- */
        close(pipefd[1]);    /* Parent only reads here; close unused write end */

        printf("[PARENT] forked producer with pid=%d\n", pid);
        printf("[WORKER-STUB] waiting to receive tasks from the pipe...\n");

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            /* ---- WORKER-STUB: replace this printf with a call that
             *      hands `buffer` off to the thread-pool/mutex code. ---- */
            printf("[WORKER-STUB] received: %-28s -> would be queued for a worker thread here\n",
                   buffer);
        }

        close(pipefd[0]);

        int status;
        waitpid(pid, &status, 0);   /* wait() for the producer child */

        if (WIFEXITED(status)) {
            printf("[PARENT] producer (pid=%d) exited normally with status %d\n",
                   pid, WEXITSTATUS(status));
        } else {
            printf("[PARENT] producer (pid=%d) did not exit normally\n", pid);
        }
    }

    return 0;
}
