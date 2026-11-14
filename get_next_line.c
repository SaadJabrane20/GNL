/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 19:01:11 by sajabran          #+#    #+#             */
/*   Updated: 2026/11/14 14:36:41 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_stash(char *stash, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buffer);
	if (!tmp)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	free(stash);
	stash = NULL;
	return (tmp);
}

static int	read_line(int fd, char **str)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	if (!*str)
		*str = ft_calloc(1, 1);
	if (!*str)
		return (free(buffer), -1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(buffer);
		if (bytes < 0)
			return (free(*str), *str = NULL, -1);
		return (0);
	}
	buffer[bytes] = '\0';
	*str = append_stash(*str, buffer);
	free(buffer);
	return (bytes);
}

static char	*update_stash(char *stash)
{
	char	*tmp;
	size_t	i;
	size_t	stash_len;

	tmp = NULL;
	if (!stash)
		return (NULL);
	i = 0;
	stash_len = ft_strlen(stash);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (i == stash_len)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	tmp = ft_strdup(stash + i);
	free(stash);
	stash = NULL;
	return (tmp);
}

static char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!stash || !*stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_calloc(i + 1, 1);
	if (line == NULL)
		return (NULL);
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (NULL);
	ret = 1;
	while (!ft_strchr(stash, '\n') && ret > 0)
		ret = read_line(fd, &stash);
	if (ret < 0)
		return (NULL);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}
