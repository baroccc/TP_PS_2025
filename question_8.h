#ifndef QUESTION_8_H
#define QUESTION_8_H

#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARGS 64
#define EXIT_CMD "exit"

#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT_MSG "enseash % "
#define BYE_MSG "Bye bye...\n"
#define ERR_READ "Error: Read failed\n"

#define PROMPT_BUFFER_SIZE 128
#define PROMPT_BASE "enseash % "
#define PROMPT_EXIT_FMT "enseash [exit:%d|%ldms] %% "
#define PROMPT_SIGN_FMT "enseash [sign:%d|%ldms] %% "

#define MILISECONDS_PER_SECONDS  1000      
#define NANOSECONDS_PER_MILISECONDS   1000000

void display_welcome_message();
void display_prompt();
void exit_shell();
int execute_command(char *command, long *execution_time);

#endif