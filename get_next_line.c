/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:57 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/18 16:49:19 by ekotova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int	fill_without_nl(t_buf_stat *st)
{
	if (!ensure_line_capacity(st, st->buf_len))
		return (0);
	ft_memcpy(st->line + st->line_len, st->buf, st->buf_pos);
	st->line_len += st->buf_len;
	return (1);
}

static char	*fill_with_nl(t_buf_stat *st)
{
	if (!ensure_line_capacity(st, st->buf_len))
		return (0);
	ft_memcpy(st->line + st->line_len, st->buf, st->buf_pos + 1);
	st->buf_pos++;
	st->line_len += st->buf_pos;
	st->buf_len -= st->buf_pos;
	ft_memcpy(st->buf, st->buf + st->buf_pos, st->buf_len);
	st->buf_pos = 0;
	st->line[st->line_len] = '\0';
	return (st->line);
}

static int	ft_read(int fd,	t_buf_stat *st)
{
	st->buf_pos = 0;
	st->buf_len = read(fd, st->buf, BUFFER_SIZE);
	if (st->buf_len < 0)
	{
		reset_state(st);
		free(st->line);
		st->line = NULL;
		return (0);
	}
	if (st->buf_len == 0)
	{
		if (st->line_len > 0)
		{
			(st->line)[st->line_len] = '\0';
			return (0);
		}
		free(st->line);
		st->line = NULL;
		return (0);
	}
	return (1);
}

static char	*build_line(int fd, t_buf_stat *st)
{
	while (1)
	{
		if (st->buf_pos == st->buf_len)
		{
			if (!ft_read(fd, st))
				return (st->line);
		}
		st->buf_pos = is_new_line(st->buf, st->buf_len, &st->is_line);
		if (!st->is_line)
		{
			if (!fill_without_nl(st))
				return (NULL);
			st->buf_pos = st->buf_len;
		}
		else
			return (fill_with_nl(st));
	}
}

char	*get_next_line(int fd)
{
	static t_buf_stat	st;

	if (fd < 0)
		return (NULL);
	if (st.current_fd != fd)
	{
		reset_state(&st);
		st.current_fd = fd;
	}
	st.line_capacity = BUFFER_SIZE + 1;
	st.line = malloc(st.line_capacity * sizeof(char));
	if (st.line == NULL)
		return (NULL);
	st.line_len = 0;
	return (build_line(fd, &st));
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