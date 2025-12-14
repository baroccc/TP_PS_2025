#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include "question_5.h"


/*
 * Writes the initial welcome message to stdout.
 * Uses strlen to avoid hardcoding the message length (magic number).
 */
void display_welcome_message() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

/*
 * Writes the standard prompt to stdout to indicate readiness.
 */
void display_prompt() {
    write(STDOUT_FILENO, PROMPT_MSG, strlen(PROMPT_MSG));
}

//Displays a goodbye message before exiting the loop.
 
void exit_shell() {
    write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
}

/*
 * Manages the execution of a command.
 * 1. Forks the current process.
 * 2. Child process replaces itself with the command using execlp.
 * 3. Parent process waits for the child to finish to prevent zombie processes.
 */
// Modified function signature to accept a pointer for the time
int execute_command(char *command, long *execution_time) {
    pid_t pid;
    int status;
    struct timespec start, end;

    // 1. Start the clock
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid = fork();
    if (pid == -1) {
        // Fork failed
        return -1;
    }
    if (pid == 0) {
        // Child process
        execlp(command, command, (char *)NULL);
        exit(EXIT_FAILURE); 
    } else {
        // Parent process
        waitpid(pid, &status, 0);

        // 2. Stop the clock after the child finishes
        clock_gettime(CLOCK_MONOTONIC, &end);

        // 3. Calculate time difference in milliseconds
        // (End Seconds - Start Seconds) * 1000 + (End Nanoseconds - Start Nanoseconds) / 1 million
        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        
        *execution_time = (seconds * MILISECONDS_PER_SECONDS) + (nanoseconds / NANOSECONDS_PER_MILISECONDS);

        return status;
    }
}