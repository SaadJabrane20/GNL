
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    char c;
    int fd = open("test.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return (1);
    }

    char *content = malloc(43);
    if (!content)
    {
        close(fd);
        return (1);
    }

    int bytes;
    int i = 0;

    while (i < 42 && (bytes = read(fd, &c, 1)) > 0)
    {
        content[i] = c;
        i++;

        if (c == '\n')
            break;
    }

    if (bytes == -1)
        perror("read");

    content[i] = '\0';

    printf("%s", content);

    free(content);
    close(fd);
    return (0);
}
