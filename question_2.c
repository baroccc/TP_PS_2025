// question2.c
// Implementation of Question 2: Simple command execution loop
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "question_2.h"

// Check for errors - // we are checking the return value.
void safe_write(int fd, const char *msg) {
    if (write(fd, msg, strlen(msg)) == -1) {
        exit(EXIT_FAILURE);
    }
}

void display_welcome_message(void) {
    safe_write(STDOUT_FILENO, WELCOME_MSG);
}

void display_prompt(void) {
    safe_write(STDOUT_FILENO, PROMPT);
}

void execute_command(char *command) {
    pid_t pid;
    int status;

    // 1. Fork the process
    pid = fork();

    // Error testing
    if (pid == -1) {
        safe_write(STDERR_FILENO, ERR_FORK);
        return;
    }

    if (pid == 0) {
        // --- Child Process ---
        execlp(command, command, (char *)NULL);
        
        // If code reaches here, execlp failed
        safe_write(STDERR_FILENO, ERR_CMD);
        exit(EXIT_FAILURE); 
    } else {
        // --- Parent Process ---
        // Wait for the child to finish
        wait(&status);
    }
}

int main(void) {
    char buffer[BUF_SIZE];
    ssize_t bytes_read;

    // 1. Display Welcome Message
    display_welcome_message();

    // 2. Start the REPL Loop (Read-Eval-Print Loop)
    while (1) {
        display_prompt();

        // a) Read command from user
        bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE);

        // Handle Ctrl+D (EOF) or read error
        if (bytes_read <= 0) {
            safe_write(STDOUT_FILENO, EXIT_MSG);
            break;
        }

        // IMPORTANT: Replace the newline '\n' with null terminator '\0'
        // read() captures the "Enter" key, which confuses execlp.
        if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
            buffer[bytes_read - 1] = '\0';
        }

        // Handle empty input (user just pressed Enter)
        if (strlen(buffer) == 0) {
            continue;
        }
        
        // b) Execute the command
        execute_command(buffer);
    }

    return 0;
}