#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 8
static int append_stash(char **stash, size_t *stash_len, char *buffer, size_t bytes)
{
    char    *new_stash;

    new_stash = malloc(*stash_len + bytes + 1);
    if (!new_stash)
        return (-1);

    if (*stash_len > 0)
        memcpy(new_stash, *stash, *stash_len);
    memcpy(new_stash + *stash_len, buffer, bytes);
    new_stash[*stash_len + bytes] = '\0';

    free(*stash);
    *stash = new_stash;
    *stash_len += bytes;
    return (0);
}

char *read_chunk(int fd)
{
    static char     *stash;
    static size_t   stash_len;
    char            buffer[BUFFER_SIZE];
    char            *result;
    ssize_t         bytes;
    size_t          chunk_len;
    size_t          remaining;

    while (stash_len < 3)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes == -1)
            return (NULL);
        if (bytes == 0)
            break;
        if (append_stash(&stash, &stash_len, buffer, bytes) == -1)
            return (NULL);
    }
    if (stash_len == 0)
        return (NULL);
    chunk_len = (stash_len < 3) ? stash_len : 3;
    result = malloc(chunk_len + 1);
    if (!result)
        return (NULL);
    memcpy(result, stash, chunk_len);
    result[chunk_len] = '\0';
    remaining = stash_len - chunk_len;
    memmove(stash, stash + chunk_len, remaining);
    stash_len = remaining;
    stash[stash_len] = '\0';
    if (stash_len == 0)
    {
        free(stash);
        stash = NULL;
    }
    return (result);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s\n", read_chunk(fd));
	printf("%s\n", read_chunk(fd));
	printf("%s\n", read_chunk(fd));
	printf("%s\n", read_chunk(fd));
	printf("%s\n", read_chunk(fd));
	printf("%s\n", read_chunk(fd));
}
