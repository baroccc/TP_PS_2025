#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h> 
#include "question_2.h"

void display_welcome_message() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

void execute_simple_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        write(STDERR_FILENO, "Error: Fork failed\n", 19);
        return;
    }

    if (pid == 0) {
        execlp(command, command, (char *)NULL);
        write(STDERR_FILENO, "Command not found\n", 18);
        exit(EXIT_FAILURE); // 
    } else {
        wait(&status);
    }
}