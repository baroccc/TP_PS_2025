#include <unistd.h>
#include <string.h>
#include "question_1.h"

void display_welcome_prompt(){
    write(STDOUT_FILENO,WELCOME_PROMPT,strlen(WELCOME_PROMPT));
}

void display_regular_prompt(){
    write(STDOUT_FILENO,WELCOME_PROMPT,strlen(WELCOME_PROMPT));
}
