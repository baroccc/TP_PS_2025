#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "question_7.h"


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
    
    char *argv[MAX_ARGS]; 
    int i = 0;

    // 1. Start the clock
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        // --- CHILD PROCESS ---

        // A. Tokenize the command string
        argv[i] = strtok(command, " \t");
        while (argv[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            argv[i] = strtok(NULL, " \t");
        }
        argv[i] = NULL; // Null-terminate the list

        if (argv[0] == NULL) { // Handle empty command
            exit(EXIT_SUCCESS);
        }

        // B. Scan for Redirections (< or >)
        // We iterate through the parsed arguments (up to 'i')
        for (int j = 0; argv[j] != NULL; j++) {
            
            // Check for Output Redirection (>)
            if (strcmp(argv[j], ">") == 0) {
                char *filename = argv[j+1]; // The file comes right after '>'
                if (filename == NULL) {
                    fprintf(stderr, "Syntax error: expected file after >\n");
                    exit(EXIT_FAILURE);
                }

                // Open file: Write Only | Create if missing | Truncate if exists
                // Permissions: rw-r--r-- (User read/write, Group read, Others read)
                int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                if (fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                // Redirect stdout (1) to this file
                dup2(fd, STDOUT_FILENO);
                close(fd);

                // Cut the arguments here so execvp doesn't see '>'
                argv[j] = NULL;
            }
            
            // Check for Input Redirection (<)
            else if (strcmp(argv[j], "<") == 0) {
                char *filename = argv[j+1];
                if (filename == NULL) {
                    fprintf(stderr, "Syntax error: expected file after <\n");
                    exit(EXIT_FAILURE);
                }

                // Open file: Read Only
                int fd = open(filename, O_RDONLY);
                if (fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                // Redirect stdin (0) to this file
                dup2(fd, STDIN_FILENO);
                close(fd);

                // Cut the arguments here
                argv[j] = NULL;
            }
        }

        // C. Execute
        execvp(argv[0], argv);
        
        perror("execvp"); 
        exit(EXIT_FAILURE); 
    } else {
        // --- PARENT PROCESS ---
        waitpid(pid, &status, 0);

        // 2. Stop the clock
        clock_gettime(CLOCK_MONOTONIC, &end);

        // 3. Calculate time
        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        *execution_time = (seconds * MILISECONDS_PER_SECONDS) + (nanoseconds / NANOSECONDS_PER_MILISECONDS);

        return status;
    }
}