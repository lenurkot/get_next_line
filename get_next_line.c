/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/10/27 13:41:33 by ekotova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
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
	char			buf[BUFSIZ];
	static size_t	line_to_read;
	int				i;

	// char			*buf;
	// static size_t	line_to_read;
	// if (fd == -1)
	// 	return (NULL);
	// buf = malloc(BUFSIZ + 1);
	// if (line_to_read > 0)
	// {
	// 	line_to_read = read(fd, buf, BUFSIZ - 1);
	// 	buf[line_to_read] = '\n';
	// }
	// printf("buf file - %s\n", buf);
	// return (buf);
	if (fd == -1)
		return (NULL);
	line_to_read = read(fd, buf, BUFSIZ - 1);
	while (buf[i] != '\n')
	{
		i++;
	}
	buf[i] = '\0';
	// printf("I've read - %s\n", buf);
	// while (line_to_read > 0)
	// {
	// 	buf[line_to_read] = '\n';
	// 	printf("I've read - %s\n", buf);
	// 	line_to_read = read(fd, buf, BUFSIZ - 1);
	// }
	return (buf);
}

int	main(int argc, char *argv[])
{
	char	*line_to_read;
	char	*name_file;
	int		fd;

	name_file = argv[1];
	fd = open(name_file, O_RDONLY);
	line_to_read = get_next_line(fd);
	// close(fd);
	printf("stirng from file - %s\n", line_to_read);
	return (0);
}
