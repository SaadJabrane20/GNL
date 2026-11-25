#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
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