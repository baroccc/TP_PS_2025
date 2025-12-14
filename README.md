# ENSEA Tiny Shell (enseash)

This project consists of a micro shell developed as part of the synthesis practical work at ENSEA. The shell is developed in C and implements the basic functionalities of a command-line interface.

## Progress Summary

### 1. Welcome Message and Prompt

**Objective:** Display a welcome message and a simple prompt to indicate the shell is ready.

-   **Implementation:** Created a `display_welcome_message` function using `write` to print the introductory text and a `display_prompt` function to show `enseash %`.
    
-   **Key functions:** `write`, `strlen`.
    

### 2. Command Execution (REPL)

**Objective:** Implement the Read-Eval-Print Loop to read user input and execute simple commands.

-   **Implementation:**
    
    -   The shell reads standard input using `read`.
        
    -   It uses `fork()` to create a child process.
        
    -   The child process executes the command using `execlp()` (without arguments for now).
        
    -   The parent process waits for the child to finish using `waitpid()` to prevent zombie processes.
        

### 3. Exit Management

**Objective:** Allow the user to exit the shell cleanly using the "exit" command or `<ctrl>+d`.

-   **Implementation:**
    
    -   **`<ctrl>+d`:** Detected when `read` returns `0` bytes.
        
    -   **"exit":** Detected by comparing the input buffer with the string "exit".
        
    -   Both cases trigger the `exit_shell()` function to print a "Bye bye..." message and terminate the loop.
        

### 4. Display Return Code or Signal

**Objective:** Update the prompt to display the exit status or the signal that terminated the previous command.

-   **Implementation:**
    
    -   The `execute_command` function now returns the `status` from `waitpid`.
        
    -   Used macros `WIFEXITED` and `WEXITSTATUS` to detect and print normal exit codes (e.g., `[exit:0]`).
        
    -   Used macros `WIFSIGNALED` and `WTERMSIG` to detect and print signals (e.g., `[sign:9]`) if the process was killed.
        
    -   The prompt is dynamically formatted using `sprintf`.
```
