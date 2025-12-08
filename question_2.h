#ifndef QUESTION_2_H
#define QUESTION_2_H

#include <unistd.h> 

// Mensajes del sistema
#define WELCOME_MSG "Welcome to ENSEA Tiny Shell :) .\nType 'exit' to quit.\n"
#define PROMPT "enseash % "

// --- Prototipos de funciones ---

// Displays welcome message
void display_welcome_message();

// Displays the prompt "enseash % "
void display_prompt();

// Takes a simple (string) command given by user, creates a child and executes it
void execute_simple_command(char *command);

#endif