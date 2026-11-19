*This project has been created as part of the 42 curriculum by sajabran.*

# <p align=center> Get Next Line </p>

## Description

Get Next Line (GNL) is a project from the 42 curriculum that focuses on file descriptor management, memory allocation, and buffered input in C.
The goal is to implement a function that reads from a file descriptor and returns one line at a time, including the newline character (\n) when present.
Unlike standard input functions such as fgets, the function must maintain its reading state between successive calls without losing unread data.
The project introduces important concepts such as:
File descriptors and the read() system call.
Static variables and persistent state.
Dynamic memory allocation and memory management.
Buffer handling and string manipulation.
Reading from multiple file descriptors simultaneously (bonus).

## Instructions

### Compilation
Compile your source files together with your own main function:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```
for the bonus part:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl
```
BUFFER_SIZE determines how many bytes are read per call to read(). It can be changed during compilation.

### Usage
Include the appropriate header:
```C
#include "get_next_line.h"
```

Call get_next_line() repeatedly until it returns NULL:
```C
int main()
{
	int fd = open("file.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```
Return values:

| **Return value** | **Meaning** |
|------------------|-------------|
|Allocated string|A line was successfully read.|
|NULL | End of file or an error occurred.|

The caller is responsible for freeing every returned line.

## Algorithm
### General Approach
The implementation uses a buffered reading algorithm with a persistent stash to preserve data between function calls.
Instead of reading one character at a time, the function reads chunks of data using read(), with each chunk having a maximum size of BUFFER_SIZE.
The algorithm follows these steps:

**Read**: Read a chunk of data from the file descriptor into a temporary buffer.<br>
**Append**: Append the newly read data to the existing stash.<br>
**Check**: Search the stash for a newline character.<br>
**Extract**: If a newline is found, extract everything up to and including it as the returned line.<br>
**Preserve**: Keep the remaining characters in the stash for the next call.<br>
**Repeat**: If no newline is found, continue reading until a newline or EOF is reached.<br>
When EOF is reached, any remaining characters in the stash are returned as the final line. If nothing remains, the function returns NULL.

### Mandatory Part

The mandatory implementation uses a single static stash to preserve unread data between successive calls.<br>
Since the function maintains its state through a static variable, it can resume reading where it left off without requiring the caller to manage the reading buffer.

### Bonus Part
The bonus implementation extends the algorithm to support multiple file descriptors simultaneously.<br>
Instead of using one static stash, it uses an array of static pointers, where each index corresponds to a file descriptor.<br>
This allows the function to maintain independent reading states for different file descriptors, even when calls are interleaved.<br>

## Resources
### Documentation
- read(): Linux manual
- open(): Linux manual
- close(): Linux manual
- malloc(): Linux manual
- GeeksforGeeks

### AI Usage
AI tools were used as learning and debugging assistants throughout the project.<br>
Their usage included:
- Understanding file descriptors, the read() system call, and buffered input.
- Learning about static variables and how persistent state works.
- Investigating edge cases involving EOF, invalid file descriptors, and different buffer sizes.

## Author
**Sjabran**<br>
42/1337 Student
