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


### 5. Execution Time Measurement

**Objective:** Measure the execution time of the launched command and display it in the shell prompt alongside the return code or signal.

-   **Implementation:**
    
    -   Modified the `execute_command` function to accept a pointer (`long *execution_time`) to store the duration.
        
    -   Used `clock_gettime` with `CLOCK_MONOTONIC` to capture the start time before `fork()` and the end time after `waitpid()` returns in the parent process.
        
    -   Calculated the elapsed time in milliseconds by computing the difference between the `timespec` structures (converting seconds and nanoseconds to milliseconds).
        
    -   Updated the prompt macros (`PROMPT_EXIT_FMT`, `PROMPT_SIGN_FMT`) to include the time format (e.g., [`exit:0|10ms`]).

### 6. Execution of a Complex Command (with arguments)

**Objective:** Enable the shell to parse and execute commands that include arguments (e.g., `ls -l` or `hostname -i`), rather than just single-word commands.

-   **Implementation:**
    
    -   Parsing: Used the `strtok` function to split the input string into tokens based on spaces and tabs (`" \t"`).
        
    -   Argument Array: Constructed an array of pointers (`argv`) to store the command and its subsequent arguments. The array is explicitly terminated with `NULL`.
        
    -   Execution: Replaced the `execlp` call with `execvp`. This function takes the filename and the array of arguments (`argv`), allowing the child process to execute complex commands correctly.


### 7. Management of Redirections to stdin and stdout

**Objective:** Implement standard input and output redirections using the `<` and `>` operators, allowing commands to read from or write to files.

-   **Implementation:**
    
    -   Argument Scanning: Before execution, the child process iterates through the `argv` array to detect redirection symbols.
        
    -   Output Redirection (`>`):

        -  Opens the target file with flags `O_WRONLY | O_CREAT | O_TRUNC` (creating the file if it doesn't exist or overwriting it).

        -  Uses `dup2(fd, STDOUT_FILENO)` to redirect the standard output to the file descriptor.
        
    -   Input Redirection (`<`):

        -  Opens the source file with `O_RDONLY`.

        -  Uses `dup2(fd, STDIN_FILENO)` to redirect the standard input to read from the file.

    -   Argument Modification: Once a redirection is processed, the operator in `argv` is replaced with `NULL` to ensure `execvp` only executes the command and its arguments, ignoring the redirection part.
    
### 8. Management of Pipe Redirection

**Objective:** Implement the pipe operator `|` to pass the standard output of one command directly as the standard input of another command.

-   **Implementation:**
    
    -   Pipeline Detection: The shell scans the arguments for the `|` symbol. If found, it splits the arguments into two separate command lists (`argv` and `argv2`).

    -   Pipe Creation: Used the `pipe(pipefd)` system call to create a unidirectional data channel.
        
    -   Dual Forking::

        -  Child 1 (Writer): Redirects its `STDOUT` to the write end of the pipe (`pipefd[1]`) and closes the read end. It executes the first command (left side of the pipe).

        -  Child 2 (Reader): Redirects its `STDIN` to the read end of the pipe (`pipefd[0]`) and closes the write end. It executes the second command (right side of the pipe).
        
    -   Resource Management: The parent process closes both pipe ends to ensure proper EOF generation and waits for both children to terminate. The exit status returned is that of the last command in the pipeline.

    -   Refactoring: Extracted the file redirection logic (`<`, `>`) into a helper function `handle_redirections` to support mixing pipes with file redirections.

```
