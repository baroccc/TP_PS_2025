#include <unistd.h>
#include <string.h>
#include <stdlib.h> 
#include "question_1.h"

// Writes the welcome message to standard output.

void display_welcome_msg(void) {
    // Write the message to STDOUT
    ssize_t bytes_written = write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
    
    // Error testing
    if (bytes_written == -1) {
        exit(EXIT_FAILURE);
    }
}


// display_prompt
void display_prompt(void) {

    // Write the prompt to STDOUT
    ssize_t bytes_written = write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    
    // Error testing
    if (bytes_written == -1) {
        exit(EXIT_FAILURE);
    }
}
