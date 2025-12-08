#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>   
#include "question_4.h"

int main(void) {
    char buffer[MAX_BUFFER_SIZE];
    
    ssize_t bytes_read;
    int status = 0;             // Stores the return status of the child process
    int command_has_run = 0;    // Flag to track if a command has been executed
    char prompt_buffer[PROMPT_BUFFER_SIZE]; // Buffer for the dynamic prompt

    display_welcome_message();

    while (1) {
        // --- Display Prompt Logic ---
        if (command_has_run == 0) {
            // Display the basic prompt for the first iteration
            write(STDOUT_FILENO, PROMPT_BASE, strlen(PROMPT_BASE));
        } else {


            // Display the prompt with the previous command's status
            if (WIFEXITED(status)) {
                
                // The process exited normally
                int exit_code = WEXITSTATUS(status);
                sprintf(prompt_buffer, PROMPT_EXIT_FMT, exit_code);
                write(STDOUT_FILENO, prompt_buffer, strlen(prompt_buffer));
            } else if (WIFSIGNALED(status)) {

                // The process was terminated by a signal
                int sig_num = WTERMSIG(status);
                sprintf(prompt_buffer, PROMPT_SIGN_FMT, sig_num);
                write(STDOUT_FILENO, prompt_buffer, strlen(prompt_buffer));
            } else {

                write(STDOUT_FILENO, PROMPT_BASE, strlen(PROMPT_BASE));
            }
        }
        // ---------------------------

        bytes_read = read(STDIN_FILENO, buffer, MAX_BUFFER_SIZE);

        if (bytes_read == -1) {
            write(STDERR_FILENO, ERR_READ, strlen(ERR_READ));
            break; // Exit on read error
        }
        if (bytes_read == 0) {
            exit_shell();
            break; // Exit on Ctrl+D (EOF)
        }

        // Replace the newline character (\n) from 'Enter' with the null terminator (\0)
        buffer[bytes_read - 1] = '\0';

        // Check for the built-in 'exit' command
        if (strcmp(buffer, EXIT_CMD) == 0) {
            exit_shell();
            break;
        }

        // execute_command must return the status from waitpid()
        // We capture it here to update the prompt in the next iteration
        status = execute_command(buffer);
        
        // Mark that we have run at least one command
        command_has_run = 1;
    }

    return 0;
}