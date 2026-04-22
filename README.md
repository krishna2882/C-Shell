## Assumptions

1. The code is compiled and executed in a Linux environment.
2. The log is maintained across sessions with a limit of 15 commands.
3. Code should be run from parent directory where log.txt is already present
4. Command related to log are not stored in history 
5. Erroneous (those which were not excited properly) commands are also stored
6. log execute command is not stored in history
7. log execute <index> - Assumed that index is 1-indexed (going from 1,2...)
8. Proclore - Assume that executable path is the one we get by using readlink() on the pid
9. Seek - Argument to search is case-sensitive
10. Echo command is executed with ""
11. peek - Colors for directories - blue, files - white, executables - green.
12. seek - assumed that flags can only be input as "-e -d" or "-e -f" or "-d" or "-f"
13. In foreground the prompt shows if the last command executed id greater than 2 seconds

## Files and Functions

### 1. `display.c`
- **Purpose**: Displays the shell prompt in the format `<username@system:current_working_dir>`.
- **Function**: 
  - `void display(char* root_dir_buffer, int size_root_dir_buffer, int* time, char* command)`: Displays the current prompt, optionally showing the time taken by the previous command if it exceeds a threshold.

### 2. `hop.c`
- **Purpose**: Implements the `hop` command, allowing the user to change directories.
- **Functions**:
  - `void hop(char *path, char* root_dir_buffer, char* previous_directory)`: Changes the current directory to the specified path.
  - `void execute_hop(char **args, int num_args, char* root_dir_buffer, char* previous_directory)`: Executes the `hop` command with the given arguments.

### 3. `log.c`
- **Purpose**: Manages command history, with capabilities to store, display, purge, and execute commands from the log.
- **Functions**:
  - `void log_f(char** args, int num_args, Queue* Q, char* root, char* previous_directory, Node* head, int* time, char* command)`: Handles log-related commands like displaying, purging, and executing commands from the history.

### 4. `proclore.c`
- **Purpose**: Provides detailed information about processes, including PID, status, process group, virtual memory, and executable path.
- **Functions**:
  - `void proc_f(int pid, char* root)`: Fetches and displays process information for a given PID.
  - `void proclore(char** args, int num_args, char* root)`: Executes the `proclore` command, providing information about the current or specified process.

### 6. `reveal.c`
- **Purpose**: Implements the `reveal` command, listing files and directories in a specified directory with options for displaying hidden files and detailed information.
- **Functions**:
  - `char* get_new_directory(char* path, char* root_dir_buffer, char* previous_directory)`: Resolves the target directory path.
  - `void function_reveal(int a, int l)`: Lists files and directories in the current directory, with options for hidden files and detailed listing.

### 7. `seek.c`
- **Purpose**: This file contains the implementation of the seek command. The command searches for files or directories within a specified target directory and supports flags such as -d, -f, and -e for directory, file, and executable search respectively.
- **Functions**:
  - File and Directory Search: Searches and filters based on the specified flags.
  - Flag Handling: Manages different search criteria based on user input.

### 8. `syst_call.c`
- **Purpose**: This file is responsible for system calls used in the shell. It includes functionality for handling process-related tasks and other system-level operations that the shell requires.
- **Functions**:
  - System Calls: Implements system call wrappers or custom handling functions needed for shell operations.

## Usage
1. Compile the code using `make`:
   ```bash
   make
