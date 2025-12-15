#ifndef QUESTION_7_H
#define QUESTION_7_H

#include <unistd.h>

#define MAX_BUFFER_SIZE 128
#define MAX_ARGS 64
#define EXIT_CMD "exit"

// System Messages
#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT_BASE_MSG "enseash % "
#define BYE_MSG "Bye bye...\n"
#define ERR_FORK "Error: Fork failed\n"
#define ERR_CMD "Command not found\n"
#define ERR_READ "Error: Read failed\n"
#define PREVIOUS_CMD "a_program"

#define PROMPT_BUFFER_SIZE 128
#define PROMPT_EXIT_FMT "enseash [exit:%d|%ldms] %% "
#define PROMPT_SIGN_FMT "enseash [sign:%d|%ldms] %% "
#define MISSING_FILE_MESSAGE1 "Missing file for >\n"
#define MISSING_FILE_MESSAGE2 "Missing file for <\n"

#define MILISECONDS_PER_SECONDS  1000      
#define NANOSECONDS_PER_MILISECONDS   1000000

// Displays the initial welcome message
void display_welcome_message();

// Displays the shell prompt
void display_prompt();

// Exits the shell cleanly with a message
void exit_shell();

// Executes the command using fork/exec/wait pattern
int execute_command(char *command, long *execution_time);

#endif