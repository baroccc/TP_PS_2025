#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "question_3.h"

//Writes the initial welcome message to stdout.
void display_welcome_message() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

//Writes the standard prompt to stdout to indicate readiness.
void display_prompt() {
    write(STDOUT_FILENO, PROMPT_MSG, strlen(PROMPT_MSG));
}

//Displays a goodbye message before exiting the loop.
 
void exit_shell() {
    write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
}

//Execute command function
void execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        write(STDERR_FILENO, ERR_FORK, strlen(ERR_FORK));
        return;
    }

    if (pid == 0) {
        // === Child Process ===
        execlp(command, command, (char *)NULL);

        write(STDERR_FILENO, ERR_CMD, strlen(ERR_CMD));
        exit(EXIT_FAILURE); 
    } else {
        // === Parent Process ===
        wait(&status);
    }
}