// question1.c
// Solution for Question 1: Display welcome message and prompt
#include <unistd.h>
#include <string.h>
#include <stdlib.h> 
#include "question_1.h"

/*
 * Function: display_welcome_msg
 * Description: Writes the welcome message to standard output.
 */
void display_welcome_msg(void) {
    // Write the message to STDOUT
    ssize_t bytes_written = write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
    
    // Error testing
    if (bytes_written == -1) {
        exit(EXIT_FAILURE);
    }
}

/*
 * Function: display_prompt
 * Description: Writes the shell prompt to standard output.
 */
void display_prompt(void) {
    // Write the prompt to STDOUT
    ssize_t bytes_written = write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    
    // Error testing
    if (bytes_written == -1) {
        exit(EXIT_FAILURE);
    }
}


 // Main function to demonstrate Question 1

int main(void) {
    // 1. Display the welcome message once
    display_welcome_msg();

    // 2. Display the prompt
    display_prompt();

    // Keep the terminal open for a moment
    char buffer[BUF_SIZE_Q1];
    read(STDIN_FILENO, buffer, BUF_SIZE_Q1); 

    return 0;
}