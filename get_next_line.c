/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/14 18:53:37 by ekotova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* The read() function shall attempt
to read nbyte bytes from the file associated
with the open file descriptor, fildes, into the
buffer pointed to by buf. The behavior of multiple
concurrent reads on the same pipe, FIFO, or terminal
device is unspecified. */
/* Read line: correct behavior
NULL: there is nothing else to read, or an error
occurred */

/**
 * @param dest str to copy
 * @param src str from which copy
 * @param n copy n-bytes, but no more the len str
 * @return void*
 */
static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*p_src;
	unsigned char		*p_dest;
	p_src = src;
	p_dest = dest;
	while (n > 0)
	{
		*p_dest = *p_src;
		p_dest++;
		p_src++;
		n--;
	}
	return (dest);
}
/**
 * @brief Make new ptr. Copy everything from str to new_str,
 * but not more than str_len. Cuz in opposite case ft_memcpy has undefined behavior.
 * free str;
 *
 * @param str string with some data;
 * @param str_len len of the str.
 * @param new_len len of tail + space for new buf;
 * @return * char* ptr to new str with another size.
 */
static char	*ft_realloc(char *str, size_t to_copy, size_t new_len)
{
	char	*new_str;

	new_str = malloc(new_len * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, str, to_copy);
	free(str);
	return (new_str);
}

int	is_new_line(char *buf, int buf_len, int *is_line)
{
	int pos;

	pos = 0;
	// printf("buf - %s\n", buf);
	while(pos < buf_len)
	{
		if (buf[pos] == '\n')
		{
			*is_line = 1;
			// if (pos == 0)
			// 	return (pos + 1);
			return (pos);
		}
		pos++;
	}
	*is_line = 0;
	return (pos);
}
static void reset_state(int *buf_pos, int *buf_len, int *is_line)
{
	*buf_pos = 0;
    *buf_len = 0;
    *is_line = 0;
}
char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static int		buf_pos = 0;
	static int		buf_len = 0;
	char			*line;
	int				line_capacity;
	int		line_len = 0;
	char 			*tmp;
	static int      current_fd;
	static int 		is_line = 0;

	if (fd < 0)
		return (NULL);

	if (current_fd != fd)
	{
		reset_state(&buf_pos, &buf_len, &is_line);
		current_fd = fd;
	}
	line_capacity = BUFFER_SIZE + 1;
	line = malloc(line_capacity * sizeof(char));
	if (line == NULL)
		return (NULL);
	while(1)
	{
		if(buf_pos == buf_len)
		{
			buf_pos = 0;
			buf_len = read(fd, buf, BUFFER_SIZE);
			if (buf_len < 0)
			{
				reset_state(&buf_pos, &buf_len, &is_line);
				free(line);
				return (NULL);
			}
			if (buf_len == 0)
			{
				if (line_len > 0)
				{
					line[line_len] = '\0';
					return (line);
				}
				free(line);
				return (NULL);
			}
		}
		buf_pos = is_new_line(buf, buf_len, &is_line);
		if (!is_line)
		{
			while (line_len + buf_len + BUFFER_SIZE + 2 > line_capacity)
			{
				line_capacity = line_capacity * 2;
				tmp = ft_realloc(line, line_len, line_capacity);
				if (tmp == NULL)
				{
					free(line);
					return (NULL);
				}
				line = tmp;
			}
			ft_memcpy(line + line_len, buf, buf_pos);
			line_len += buf_len;
			buf_pos = buf_len;
		}
		else
		{
			ft_memcpy(line + line_len, buf, buf_pos + 1);
			buf_pos++;
			line_len += buf_pos;
			buf_len -= buf_pos;
			ft_memcpy(buf, buf + buf_pos, buf_len);
			buf_pos = 0;
			line[line_len] = '\0';
			return (line);
		}
	}
}
// int	main(int argc, char *argv[])
// {
// 	char	*name_file;
// 	char	*line_to_read = "";
// 	int		fd;
// 	int 	i = 1;

// 	name_file = argv[argc - 1];
// 	fd = open(name_file, O_RDONLY);
// 	// fd = 0;
// 	while (line_to_read != NULL)
// 	{
// 		line_to_read = get_next_line(fd);
// 		printf("%d) %s\n", i, line_to_read);
// 		free(line_to_read);
// 		i++;
// 	}
// 	return (0);
// }