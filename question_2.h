// question_2.h
// Header for Question 2: REPL (Read-Eval-Print Loop)
#ifndef QUESTION_2_H
#define QUESTION_2_H

#include <unistd.h>

<<<<<<< HEAD
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
=======
// Buffer size for command input
#define BUF_SIZE 1024

// System Messages 
#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT "enseash % "
#define EXIT_MSG "\nBye bye...\n"

// Error Messages defined as constants 
#define ERR_FORK "Error: Fork failed\n"
#define ERR_CMD "Command not found\n"
#define ERR_WRITE "Error writing to stdout\n"

// --- Function Prototypes ---

// Displays welcome message with error checking
void display_welcome_message(void);

// Displays the prompt "enseash % " with error checking
void display_prompt(void);

// Executes the command using fork/exec/wait
>>>>>>> origin/HEAD
void execute_command(char *command);

#endif