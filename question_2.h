// question_2.h
// Header for Question 2: REPL (Read-Eval-Print Loop)
#ifndef QUESTION_2_H
#define QUESTION_2_H

#include <unistd.h>

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
void execute_command(char *command);

#endif