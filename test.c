#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE = 8


int count_file_chars(int fd)
{
	int count = 0;
	char c;
	int i;
	while((i = (read(fd, &c, 1))) > 0)
		count++;
	return count;
}
int read_counter(int fd)
{
	static int count;
	char c;
	if (read(fd, &c, 1) == -1)
		return count;
	count += 1;
	return count;

}

char *read_n_chars(int fd, int n)
{
	char *str = malloc(n);
	if (read(fd, str, n) == -1)
		return NULL;
	return str;
}
size_t ft_strlen(const char *s)
{
	int i = 0;
	if (s == NULL)
		return 0;
	while(s[i])
		i++;
	return i;
}
char *read_chunk(int fd)
{
	char *buffer = malloc(BUFFER_SIZE + 1);
	char *str = malloc(4);
	static char *stash;
	if (ft_strlen(stash) > 0)
	{
		memmove(str, stash, 3);
		str[4] = '\0';
		memmove(stash, stash + 3, BUFFER_SIZE);
		return str;
	}
	else if (ft_strlen(stash) < 3 && ft_strlen(stash) > 0)
	{
		if (read(fd, buffer, BUFFER_SIZE) == -1)
			return NULL;

	}
	if (read(fd, buffer, BUFFER_SIZE) == -1)
		return NULL;
	memmove(str, buffer, 3);
	str[3] = '\0';
	stash = &buffer[3];
	return str;
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return 0;
	printf("%s\n", read_chunk(fd));
	printf("%s\n", read_chunk(fd));
	printf("%s\n", read_chunk(fd));
	close(fd);
}
