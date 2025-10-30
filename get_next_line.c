/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/10/30 16:02:09 by ekotova          ###   ########.fr       */
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

// static	ft_read(void)
// static void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	const unsigned char	*p_src;
// 	unsigned char		*p_dest;

// 	p_src = src;
// 	p_dest = dest;
// 	while (n > 0)
// 	{
// 		*p_dest = *p_src;
// 		p_dest++;
// 		p_src++;
// 		n--;
// 	}
// 	return (dest);
// }
// static char	*ft_realloc(size_t s_len)
// {
// 	char	*ptr;

// 	ptr = malloc(s_len * sizeof(char));
// 	if (ptr == NULL)
// 		return (NULL);
// 	return (ptr);
// }

static size_t ft_def_len(char *str)
{
	size_t	len;

	len = 0;
	while(str[len] != '\n')
	{
		len++;
	}
	if (str[len] == '\n')
		return (len + 1);
	return (len);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	static char		*str_to_return;
	// static size_t	str_to_return_len;
	static size_t	line_to_read;
	int				i;

	if (fd == -1)
		return (NULL);
	printf("buf sting = %s\n",buf );
	if (buf)
	{
		printf("im not empty!!!!\n");
		printf("In buf - %s\n", buf);
	}
	else
	{
		printf("im here\n");
		buf = malloc(BUFFER_SIZE * sizeof(char));
		if (buf == NULL)
			return (NULL);
		str_to_return = malloc(BUFFER_SIZE * sizeof(char));
		if (str_to_return == NULL)
			return (NULL);
		printf("I allocarte mem\n");
	}
	i = 0;
	line_to_read = read(fd + i, buf, BUFFER_SIZE);
	if (line_to_read == -1)
		return (NULL);
	// str_to_return_len = ft_def_len(buf);
	// printf("line_to_read - %zu buf_size = %d str_to_return_len - %zu\n", line_to_read, BUFFER_SIZE, str_to_return_len);

	while (i <= BUFFER_SIZE && *buf != '\n')
	{
		// printf("*buf = %c\n", *buf);
		str_to_return[i] = *buf;
		// printf("*str_to_return[i] = %c\n", str_to_return[i]);
		buf++;
		i++;
	}
	if (*buf == '\n')
		str_to_return[i] = '\n';
	return (str_to_return);




	// printf("read line - %zu, line - %s\n", read_line, str);
	// printf("i m gonna crush\n");
	// read_line = read(fd, buf, BUFFER_SIZE - 1);
	// printf("read line - %zu\n", read_line);
	// printf("you don't see me\n");
	// buf[read_line] = '\n';
	// while (buf[i] != '\n' || buf[i])
	// {
	// 	printf("i was here\n");
	// 	str[i] = buf[i];
	// 	i++;
	// }
	// if (buf[i] != '\n')
	// 	str[i] = '\n';
	// printf("read line - %zu, line - %s\n", read_line, str);
	// while (read_line > 0)
	// {
	// 	buf[read_line] = '\n';
	// 	read_line = read(fd, buf, BUFFER_SIZE - 1);
	// }
	// return (str_to_ret);
}

int	main(int argc, char *argv[])
{
	char	*name_file;
	char	*line_to_read;
	int		fd;

	name_file = argv[argc - 1];
	// printf("name file - %s\n, argc = %d\n", argv[argc - 1], argc);
	fd = open(name_file, O_RDONLY);
	line_to_read = get_next_line(fd);
	// line_to_read = get_next_line(fd);
	// close(fd);
	//printf("stirng from file - %s\n", line_to_read);
	line_to_read = get_next_line(fd);
	// printf("stirng from file - %s\n", line_to_read);
	// line_to_read = get_next_line(fd);
	// printf("stirng from file - %s\n", line_to_read);
	return (0);
}
