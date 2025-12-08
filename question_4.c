#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "question_4.h"

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
int execute_command(char *command) {
    pid_t pid;
    int status;

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
        return status;
    }
}