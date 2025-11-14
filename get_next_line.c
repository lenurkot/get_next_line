/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/14 13:55:45 by ekotova          ###   ########.fr       */
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
// int ft_str_len(char *line)
// {
// 	int	i;

// 	while(line[i] != '\0')
// 	{
// 		// printf("%c - %d\n", line[i], line[i]);
// 		i++;
// 	}
// 	return i;
// }
// void print_sym_code(char *str, int len)
// {
// 	int i = 0;
// 	while(i < len)
// 	{
// 		printf("%d) %d - %c\n", i + 1, str[i], str[i]);
// 		i++;
// 	}
// }
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

/**
 * @brief go through the string and look for '\n' and return eather potential len or 0
 *
 * @param str string
 * @param buf_size always equal BUFFER size
 * @return len of the new line if i found '\n' or 0 if i didn't. +1 for '\n'
 */
// void new_line(char *line, char *buf, size_t buf_size)
// {
// 	int	i;

// 	i = 0;
// 	while(i < buf_size)
// 	{
// 		if (buf[i] == '\n')
// 		{
// 			i++;
// 			ft_memcpy(line, buf, i);
// 			line[i] = '\0';
// 			buf_size -= i;
// 			ft_memcpy(buf, buf + i, buf_size);
// 			return ;
// 		}
// 		i++;
// 	}
// 	ft_memcpy(line, buf, buf_size);
//     line[buf_size] = '\0';
//     buf_size = 0;
// }
char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static int		buf_pos = 0;
	static int		buf_len = 0;
	static char		*line;
	static int		line_capacity = 0;
	static int		line_len = 0;
	char 			*tmp;

	if (fd < 0)
		return (NULL);
	if(buf_pos == buf_len)
	{
		buf_len = read(fd, buf, BUFFER_SIZE);
		if (buf_len == 0)
		{
			if (line != NULL)
				return (line);
			return (NULL);
		}
		buf_pos = 0;
	}

	if (line == NULL)
	{
		line_capacity = 100;
		line = malloc(100 + sizeof(char));
		if (line == NULL)
			return (NULL);
	}

	while (1)
	{
		if (buf_len == 0)
			break ;
		else if (line_len + 2 > line_capacity)
		{
			line_capacity = line_capacity * 2;
			tmp = ft_realloc(line, line_len, line_capacity);
			if (tmp == NULL) // looks like everything is ok here?
				return (NULL);
			line = tmp;
		}
		else if (buf_pos == buf_len)
		{
			buf_len = read(fd, buf, BUFFER_SIZE);
			if (buf_len == 0)
				break;
			buf_pos = 0;
		}
		else
		{
			line[line_len] = buf[buf_pos];
			line_len++;
			buf_pos++;
			if (line[line_len - 1] == '\n')
				break ;
		}
	}
	if (line_len > 0)
	{
		line[line_len] = '\0';
		line_len = 0;
		return (line);
	}
	return (NULL);
}
// int	main(int argc, char *argv[])
// {
// 	char	*name_file;
// 	char	*line_to_read;
// 	int		fd;
// 	int 	i = 1;

// 	name_file = argv[argc - 1];
// 	// fd = open(name_file, O_RDONLY);
// 	fd = 0;
// 	while (line_to_read != NULL)
// 	{
// 		line_to_read = get_next_line(fd);
// 		printf("%d) %s\n", i, line_to_read);
// 		i++;
// 	}
// 	return (0);
// }
