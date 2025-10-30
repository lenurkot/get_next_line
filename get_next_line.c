/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/10/30 14:05:50 by ekotova          ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	char			*str;
	static size_t	read_line;
	int				i;

	i = 0;
	if (fd == -1)
		return (NULL);
	str = malloc(BUFFER_SIZE + 1);
	if (str == NULL)
		return (NULL);
	read_line = read(fd + i, buf, BUFFER_SIZE - 1);
	buf[read_line] = '\n';
	while (buf[i] != '\n')
	{
		str[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		str[i] = '\n';
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
	return (str);
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
	printf("stirng from file - %s\n", line_to_read);
	line_to_read = get_next_line(fd);
	printf("stirng from file - %s\n", line_to_read);
	// line_to_read = get_next_line(fd);
	// printf("stirng from file - %s\n", line_to_read);
	return (0);
}
