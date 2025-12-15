#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "question_8.h"

void display_welcome_message() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

void exit_shell() {
    write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
    exit(0);
}

// Helper function to handle redirections (<, >) for a single process
void handle_redirections(char **argv) {
    for (int j = 0; argv[j] != NULL; j++) {
        if (strcmp(argv[j], ">") == 0) {
            char *filename = argv[j+1];
            if (filename == NULL) { write(STDERR_FILENO, MISSING_FILE_MESSAGE1, strlen(MISSING_FILE_MESSAGE1)); exit(EXIT_FAILURE); }
            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (fd == -1) { perror("open >"); exit(EXIT_FAILURE); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            argv[j] = NULL; // Truncate args
        } else if (strcmp(argv[j], "<") == 0) {
            char *filename = argv[j+1];
            if (filename == NULL) { write(STDERR_FILENO, MISSING_FILE_MESSAGE2, strlen(MISSING_FILE_MESSAGE2)); exit(EXIT_FAILURE); }
            int fd = open(filename, O_RDONLY);
            if (fd == -1) { perror("open <"); exit(EXIT_FAILURE); }
            dup2(fd, STDIN_FILENO);
            close(fd);
            argv[j] = NULL; // Truncate args
        }
    }
}

int execute_command(char *command, long *execution_time) {
    int status;
    struct timespec start, end;
    char *argv[MAX_ARGS]; 
    int i = 0;

    // Start timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Parse tokens
    argv[i] = strtok(command, " \t");
    while (argv[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        argv[i] = strtok(NULL, " \t");
    }
    argv[i] = NULL;

    if (argv[0] == NULL) return 0; // Empty command

    // Check for Pipe (|)
    int pipe_idx = -1;
    for (int j = 0; argv[j] != NULL; j++) {
        if (strcmp(argv[j], "|") == 0) {
            pipe_idx = j;
            break;
        }
    }

    // --- PIPELINE LOGIC ---
    if (pipe_idx != -1) {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return -1;
        }

        // Split arguments into two parts
        argv[pipe_idx] = NULL;            // Terminate first command
        char **argv2 = &argv[pipe_idx + 1]; // Start of second command

        // Child 1 (Writer)
        pid_t pid1 = fork();
        if (pid1 == 0) {
            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write
            close(pipefd[0]); // Close unused read end
            close(pipefd[1]); // Close original write end
            execvp(argv[0], argv);
            perror("execvp child1"); exit(EXIT_FAILURE);
        }

        // Child 2 (Reader)
        pid_t pid2 = fork();
        if (pid2 == 0) {
            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read
            close(pipefd[1]); // Close unused write end
            close(pipefd[0]); // Close original read end
            execvp(argv2[0], argv2);
            perror("execvp child2"); exit(EXIT_FAILURE);
        }

        // Parent
        close(pipefd[0]);
        close(pipefd[1]);
        
        // Wait for both, but we return the status of the LAST command (pid2)
        int status1;
        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status, 0); 
    } 
    // --- SINGLE COMMAND LOGIC ---
    else {
        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return -1; }
        
        if (pid == 0) {
            handle_redirections(argv); // Handle < or >
            execvp(argv[0], argv);
            perror("execvp"); exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);
        }
    }

    // Stop timer
    clock_gettime(CLOCK_MONOTONIC, &end);
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    *execution_time = (seconds * MILISECONDS_PER_SECONDS) + (nanoseconds / NANOSECONDS_PER_MILISECONDS);

    return status;
}