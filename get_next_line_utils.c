/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 15:34:16 by sajabran          #+#    #+#             */
/*   Updated: 2026/11/10 21:06:14 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d < s)
	{
		while (n > 0)
		{
			*d++ = *s++;
			n--;
		}
	}
	else if (d > s)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return 0;
	while(s[i])
		i++;
	return i;
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	i = 0;
	dest = malloc(sizeof(char) * (s_len + 1));
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;

	i = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (size <= dest_len)
		return (src_len + size);
	while (src[i] != '\0' && ((i + dest_len) < size - 1))
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	dst[i + dest_len] = '\0';
	return (src_len + dest_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcat(str, s1, s1_len + s2_len + 1);
	ft_strlcat(str, s2, s1_len + s2_len + 1);
	return (str);
}

