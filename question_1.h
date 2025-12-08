// question_1.h
// Header file containing constants for Question 1
#ifndef QUESTION_1_H
#define QUESTION_1_H

#include <unistd.h> 

// Constants definition
#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\n"
#define PROMPT "enseash % "
#define BUF_SIZE_Q1 10

// Function prototypes
void display_welcome_msg(void);
void display_prompt(void);

#endif