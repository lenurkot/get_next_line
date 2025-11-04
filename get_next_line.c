/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/04 12:11:24 by ekotova          ###   ########.fr       */
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

static int ft_str_len(char *str, size_t buf_size_str)
{
	int	len;

	len = 0;
	while(len <= buf_size_str)
		len++;
	return (len);
}

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
static char	*ft_realloc(char *str, size_t size, size_t str_to_return_len, char *str_to_free)
{
	char *new_str;

	new_str = malloc(size * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, str, size);
	free(str_to_free);
	return (new_str);
}

static int is_new_line(char *str, size_t buf_size)
{
	int	i;

	i = 0;
	while(i < buf_size)
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}
char	*get_next_line(int fd)
{
	static int		read_result;
	static char		buf[BUFFER_SIZE];
	static char		*p_to_buf;
	static char		*str_to_return;
	static size_t	str_to_return_len = 0;
	static size_t	str_to_read_copied;
	static size_t	str_to_read_buf;
	static int		buf_size;
	static int		count_read = 1;


	if (fd == -1)
		return (NULL);
	buf_size = BUFFER_SIZE;
	if (str_to_return_len == 0)
	{
		read_result = read(fd, buf, BUFFER_SIZE);
		if (read_result == -1)
			return (NULL);
		p_to_buf = buf;

	}
	if (buf_size == BUFFER_SIZE)
	{
		str_to_read_buf = count_read * BUFFER_SIZE * sizeof(char);
		str_to_return = malloc(str_to_read_buf);
		if (str_to_return == NULL)
			return (NULL);
		count_read++;
	}

	// if (!is_new_line(p_to_buf, BUFFER_SIZE))
	// {
	// 	str_to_read_copied = BUFFER_SIZE - buf_size;
	// 	str_to_read_buf = buf_size + BUFFER_SIZE;
	// 	str_to_return = ft_realloc(p_to_buf, buf_size + BUFFER_SIZE, str_to_return_len, str_to_return);
	// 	buf_size = BUFFER_SIZE;
	// 	// printf("str_to_return - %s\n", str_to_return);
	// 	read_result = read(fd, buf, BUFFER_SIZE);
	// 	if (read_result == -1)
	// 		return (NULL);
	// 	p_to_buf = buf;
	// }
	// else
	// {
	// 	str_to_read_buf = BUFFER_SIZE * sizeof(char);
	// 	str_to_return = malloc(str_to_read_buf);
	// 	if (str_to_return == NULL)
	// 		return (NULL);
	// }

	if (is_new_line(p_to_buf, buf_size))
	{
		printf("\np_to_buf - %s\n", p_to_buf);
		ft_memcpy(str_to_return, p_to_buf, is_new_line(p_to_buf, BUFFER_SIZE));
		str_to_return_len = is_new_line(p_to_buf, BUFFER_SIZE);
		buf_size = buf_size - str_to_return_len;
		p_to_buf = p_to_buf + str_to_return_len;


		return (str_to_return);
	}
	else
	{
		str_to_return_len = buf_size;
		count_read++;
		printf("\np_to_buf - %s\n", p_to_buf);
		// str_to_return_len = ft_str_len(str_to_return, BUFFER_SIZE - str_to_read_copied);
		// ft_memcpy(str_to_return + str_to_return_len, buf, BUFFER_SIZE);
		str_to_return = ft_realloc(p_to_buf, count_read * BUFFER_SIZE, str_to_return_len, str_to_return);
		if (str_to_return == NULL)
			return (NULL);
		printf("str_to_return - %s\n", str_to_return);
		get_next_line(fd);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	char	*name_file;
	char	*line_to_read;
	int		fd;

	name_file = argv[argc - 1];
	fd = open(name_file, O_RDONLY);
	line_to_read = get_next_line(fd);
	//printf("stirng from file - %s\n", line_to_read);
	//line_to_read = get_next_line(fd);
	//printf("stirng from file - %s\n", line_to_read);
	//line_to_read = get_next_line(fd);
	//printf("stirng from file - %s\n", line_to_read);
	return (0);
}
