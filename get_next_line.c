/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/04 18:13:48 by ekotova          ###   ########.fr       */
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


// /* if dest>src -> copy from the right to the lft */
// void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	const char	*p_src;
// 	char		*p_dest;

// 	p_src = src;
// 	p_dest = dest;
// 	while (n > 0)
// 	{
// 		if (p_dest > p_src)
// 		{
// 			*(p_dest + n - 1) = *(p_src + n - 1);
// 		}
// 		if (p_dest <= p_src)
// 		{
// 			*p_dest = *p_src;
// 			p_dest++;
// 			p_src++;
// 		}
// 		n--;
// 	}
// 	return (dest);
// }
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
	// printf("&&&&&&&&&&&&\n");
	// print_sym_code(src, n);
	// printf("&&&&&&&&&&&&\n");
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
static char	*ft_realloc(char *str, size_t str_len, size_t new_len)
{
	char	*new_str;
	size_t	to_copy;

	printf("in real str = %s, size - %zu\n", str, new_len);
	print_sym_code(str, new_len);
	to_copy = str_len;
	if (new_len != 0)
		new_str = malloc(new_len * sizeof(char));
	else
		new_str = malloc(str_len * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	if (new_len != 0 && str_len < new_len)
		to_copy = new_len;
	ft_memcpy(new_str, str, to_copy);
	printf("************\n");
	print_sym_code(new_str, str_len);
	printf("************\n");
	free(str);
	// printf("in real new_str = %s, size - %zu\n", new_str, new_len);
	return (new_str);
}

/**
 * @brief go through the string and look for '\n' and return eather potential len or 0
 *
 * @param str string
 * @param buf_size always equal BUFFER size
 * @return len of the new line if i found '\n' or 0 if i didn't. +1 for '\n'
 */
static int len_of_new_line(char *str, size_t buf_size)
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

char *give_me_fucking_line(char *buf, int buf_len)
{
	static char		*tmp_line;
	static int		tmp_line_len;
	tmp_line_len = len_of_new_line(buf, buf_len);

	// printf("************\n");
	// printf("len - %d, buf - %s, bufsize - %zu\n", tmp_line_len, buf, sizeof(buf));
	print_sym_code(buf, tmp_line_len);
	// printf("************\n");

	if (!tmp_line)
		tmp_line = malloc(BUFFER_SIZE * sizeof(char));
	if (tmp_line_len != 0)
		tmp_line = malloc(tmp_line_len * sizeof(char));
	if (tmp_line == NULL)
		return (NULL);
	ft_memcpy(tmp_line, buf, tmp_line_len);
	return (tmp_line);
}

void im_gonna_accumulate(char *buf, int buf_len)
{
	static char		*tmp_line;
	static int		tmp_line_len;
	tmp_line_len = len_of_new_line(buf, buf_len);
}
char	*get_next_line(int fd)
{
	static int		read_result;
	static char		*buf;
	static size_t	buf_len;
	static size_t	tail_buf = 0;
	static size_t	line_tail_len = 0;
	static char		*line;
	static int		line_len;


	if (fd == -1)
		return (NULL);

	if (tail_buf == 0)
	{
		buf = malloc(BUFFER_SIZE * sizeof(char));
		if (buf == NULL)
			return (NULL);
		read_result = read(fd, buf, BUFFER_SIZE);
		if (read_result <= 0)
			return (NULL);
		buf_len = read_result;
	}

	line_len = len_of_new_line(buf, buf_len);
	while (len_of_new_line(buf, buf_len))
	{
		tail_buf = buf_len;
		line = give_me_fucking_line(buf, line_len);
		buf_len = buf_len - line_len;
		ft_memcpy(buf, buf + line_len, buf_len);
		return (line);
	}
	// else
	// {
	// }


	// // printf("im here agin. buf - %s, buf - %zu\n", buf, buf_len);
	// if (line_len != 0)
	// {
	// 	ft_memcpy(line, buf, line_len);
	// 	tail_buf = buf_len - line_len;
	// 	/*if i move ptr buf, then i will lose the
	// 	start position of buf and won't free everything*/
	// 	ft_memcpy(buf, buf + line_len, tail_buf);
	// 	buf_len = tail_buf;
	// 	line_tail_len = 0;
	// 	return (line);
	// }
	// else
	// {
	// 	if (buf_len > 0)
	// 	{
	// 		// printf("line_tail_len - %zu\n", line_tail_len);
	// 		if (line_tail_len == 0)
	// 		{
	// 			printf("||||||||||||");
	// 			line = ft_realloc(buf, buf_len, buf_len);
	// 			if (line == NULL)
	// 				return (NULL);
	// 			line_tail_len = line_tail_len + buf_len;
	// 			printf("||||||||||||");
	// 			// printf("line - %s len = %zu\n", line, line_tail_len);
	// 		}
	// 		else
	// 		{
	// 			line_tail_len = line_tail_len + buf_len;
	// 			printf("\n\n");
	// 			ft_realloc(line, line_tail_len, line_tail_len);
	// 			if (line == NULL)
	// 				return (NULL);
	// 			ft_memcpy(line + line_tail_len, buf, buf_len);
	// 			printf("------------------n - %zu, line - %c\n", line_tail_len, *line);
	// 			print_sym_code(line, line_tail_len);
	// 			printf("\n\n");
	// 			// printf("AFTER line - %s\n", line);
	// 		}
	// 	}
	// 	tail_buf = 0;
	// 	line_len = buf_len;
		return (get_next_line(fd));
}

int	main(int argc, char *argv[])
{
	char	*name_file;
	char	*line_to_read;
	int		fd;

	name_file = argv[argc - 1];
	fd = open(name_file, O_RDONLY);
	line_to_read = get_next_line(fd);
	printf("stirng from file - %s\n", line_to_read);
	line_to_read = get_next_line(fd);
	printf("stirng from file - %s\n", line_to_read);
	line_to_read = get_next_line(fd);
	printf("stirng from file - %s\n", line_to_read);
	// line_to_read = get_next_line(fd);
	return (0);
}
