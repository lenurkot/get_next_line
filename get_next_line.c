/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/05 20:29:10 by ekotova          ###   ########.fr       */
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
int ft_str_len(char *line)
{
	int	i;

	while(line[i] != '\0')
	{
		// printf("%c - %d\n", line[i], line[i]);
		i++;
	}
	return i;
}
char print_sym_code(char *str, int len)
{
	int i = 0;
	while(i < len)
	{
		printf("%d) %d - %c\n", i + 1, str[i], str[i]);
		i++;
	}
}
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
void new_line(char *line, char *buf, size_t buf_size)
{
	int	i;

	i = 0;
	while(i < buf_size)
	{
		if (buf[i] == '\n')
		{
			i++;
			ft_memcpy(line, buf, i);
			line[i] = '\0';
			buf_size -= i;
			ft_memcpy(buf, buf + i, buf_size);
			return ;
		}
		i++;
	}
	ft_memcpy(line, buf, buf_size);
    line[buf_size] = '\0';
    buf_size = 0;
}
char	*get_next_line(int fd)
{
	// static int	 buf_size;
	// static char		*buf;
	// static char		*line;
	// static size_t	line_read = 0;
	// static char		*tmp;
	static size_t		buf_size;
	static char	*buf;
	static char	*line;
	size_t	line_read = 0;
	char	*tmp;

	if (fd == -1)
		return (NULL);
	if (!buf && !line)
	{
		buf = malloc(BUFFER_SIZE * sizeof(char));
		if (buf == NULL)
			return (NULL);

		line = malloc(BUFFER_SIZE * sizeof(char));
		if (buf == NULL)
			return (NULL);
		buf_size = read(fd, buf, BUFFER_SIZE);
		if  (buf_size <= 0)
			return (NULL);
	}

	// 1 case
	// while (1)
	// {
	// 	if  (buf_size > 0)
	// 	{
	// 		ft_memcpy(line + line_read, buf, buf_size);
	// 		line_read += buf_size;
	// 		line[line_read] = '\0';
	// 		buf_size -= buf_size;
	// 	}
	// 	else
	// 	{
	// 		tmp = ft_realloc(line, line_read, line_read * BUFFER_SIZE);
	// 		if (tmp == NULL)
	// 			return (NULL);
	// 		line = tmp;
	// 		line[line_read] = '\0';
	// 		if (get_next_line(fd) == NULL)
	// 			break;
	// 	}
	// }

	// 2 case
	line[buf_size] = '\0';
	while  (buf_size != 0)
	{
		// printf("buf_size - %d buf - %s", buf_size, buf);
		new_line(line + line_read, buf, buf_size);
		line_read += ft_str_len(line);
		// buf += line_read;
		// printf("buf_size AFTER - %d buf - %s", buf_size, buf);
		if (line_read == 0)
        	break;
		return (line);
		// ft_memcpy(line, buf, buf_size);
		// line[buf_size] = '\0';
		// line_read += buf_size;
		// if (line_read == buf_size)
		// 	break;
		// get_next_line(fd);
	}
	// }
	// free();
	return (line);
}
int	main(int argc, char *argv[])
{
	char	*name_file;
	char	*line_to_read;
	int		fd;

	name_file = argv[argc - 1];
	fd = open(name_file, O_RDONLY);
	line_to_read = get_next_line(fd);
	// printf("\nFIRST\n%s*****\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\nSECOND\n%s*****\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\nTHIRD\n%s*****\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\nFOURTH\n%s*****\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\nFIFTH\n %s\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\n6th\n%s\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\n7th\n%s\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\n8thn %s\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\n9th\n%s\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("\n10th\n%s\n", line_to_read);
	line_to_read = get_next_line(fd);
	print_sym_code(line_to_read, 250);
	//printf("\n11th\n %s\n", line_to_read);
	// line_to_read = get_next_line(fd);
	// printf("\n12th\n%s\n", line_to_read);
	// free(line_to_read);
	// line_to_read = get_next_line(fd);
	// printf("stirng from file - %s\n", line_to_read);
	return (0);
}
