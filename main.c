#include <unistd.h>
#include <string.h>
#include "question_3.h"

int main(void) {
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read;

    display_welcome_message();

    while (1) {
        display_prompt();

        bytes_read = read(STDIN_FILENO, buffer, MAX_BUFFER_SIZE);

        if (bytes_read == -1) {
            write(STDERR_FILENO, ERR_READ, strlen(ERR_READ));
            break; // Exit on read error
        }
        if (bytes_read == 0) {
            exit_shell();
            break;
        }

        // Replace the newline character (\n) from 'Enter' with the null terminator (\0)
        buffer[bytes_read - 1] = '\0';

        // Check for the built-in 'exit' command
        if (strcmp(buffer, EXIT_CMD) == 0) {
            exit_shell();
            break;
        }

        // Delegate execution to the specialized function
        execute_command(buffer);
    }

    return 0;
}