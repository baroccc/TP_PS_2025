#ifndef QUESTION_3_H
#define QUESTION_3_H

#include <unistd.h>

#define MAX_BUFFER_SIZE 128
#define EXIT_CMD "exit"

// System Messages
#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT_MSG "enseash % "
#define BYE_MSG "Bye bye...\n"
#define ERR_FORK "Error: Fork failed\n"
#define ERR_CMD "Command not found\n"
#define ERR_READ "Error: Read failed\n"

// Displays the initial welcome message
void display_welcome_message();

// Displays the shell prompt
void display_prompt();

// Exits the shell cleanly with a message
void exit_shell();

// Executes the command using fork/exec/wait pattern
void execute_command(char *command);

#endif