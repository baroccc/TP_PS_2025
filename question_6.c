#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "question_6.h"


//Writes the initial welcome message to stdout.
void display_welcome_message() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

//Writes the standard prompt to stdout to indicate readiness.
void display_prompt() {
    write(STDOUT_FILENO, PROMPT_BASE_MSG, strlen(PROMPT_BASE_MSG));
}

//Displays a goodbye message before exiting the loop.
 
void exit_shell() {
    write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
}

// Modified function signature to accept a pointer for the time
int execute_command(char *command, long *execution_time) {
    pid_t pid;
    int status;
    struct timespec start, end;
    
    // Array to store the command and its arguments
    char *argv[MAX_ARGS]; 
    int i = 0;

    // Start the clock
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid = fork();
    if (pid == -1) {
        // Fork failed
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        // --- CHILD PROCESS ---
        
        // Tokenize the command string (split by space and tab)
        argv[i] = strtok(command, " \t");
        
        while (argv[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            argv[i] = strtok(NULL, " \t");
        }
        // The last element of argv must be NULL for execvp
        argv[i] = NULL;

        // If no command was entered (empty input), exit child
        if (argv[0] == NULL) {
            exit(EXIT_SUCCESS);
        }

        // Use execvp to execute the command with arguments
        execvp(argv[0], argv);
        
        // If execvp returns, it means an error occurred (e.g., command not found)
        perror("execvp"); 
        exit(EXIT_FAILURE); 
    } else {
        // --- PARENT PROCESS ---
        waitpid(pid, &status, 0);

        // Stop the clock
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculate time in milliseconds
        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        *execution_time = (seconds * MILISECONDS_PER_SECONDS) + (nanoseconds / NANOSECONDS_PER_MILISECONDS);

        return status;
    }
}