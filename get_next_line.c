/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:14:41 by sajabran          #+#    #+#             */
/*   Updated: 2026/11/19 16:59:13 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_append_stash(char *stash, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buffer);
	if (tmp == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	free(stash);
	stash = NULL;
	return (tmp);
}

static int	ft_read_line(int fd, char **stash)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (-1);
	if (!*stash)
	{
		*stash = ft_calloc(1, 1);
		if (!*stash)
			return (free(buffer), -1);
	}
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
		free(*stash);
		*stash = NULL;
	}
	else if (bytes > 0)
	{
		buffer[bytes] = '\0';
		*stash = ft_append_stash(*stash, buffer);
	}
	free(buffer);
	return (bytes);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
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

static char	*ft_update_stash(char *stash)
{
	char	*tmp;
	int		i;
	int		stash_len;

	i = 0;
	tmp = NULL;
	if (stash == NULL)
		return (NULL);
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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			bytes;

	bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(stash, '\n') && bytes > 0)
		bytes = ft_read_line(fd, &stash);
	if (bytes < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_extract_line(stash);
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_update_stash(stash);
	return (line);
}
