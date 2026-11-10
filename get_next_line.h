/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 18:58:46 by sajabran          #+#    #+#             */
/*   Updated: 2026/11/10 21:02:40 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 42

void *ft_memmove(void *dest, const void *src, size_t n);
char *ft_strjoin(char const *s1, char const *s2);

#endif
