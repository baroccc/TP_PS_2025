#include <unistd.h>
#include <string.h>
#include "question_2.h"

#define MAX_SIZE 128

int main(void) {
    char buffer[MAX_SIZE];
    ssize_t bytes_read;


    display_welcome_message();


    while (1) {
        display_prompt();

        // read users command
        bytes_read = read(STDIN_FILENO, buffer, MAX_SIZE);


        if (bytes_read == 0) {
            write(STDOUT_FILENO, "\nBye bye...\n", 12);
            break;
        }


        buffer[bytes_read - 1] = '\0';

        // Detect "exit command"
        if (strcmp(buffer, "exit") == 0) {
            write(STDOUT_FILENO, "Bye bye...\n", 11);
            break;
        }

        
        execute_simple_command(buffer);
    }

    return 0;
}