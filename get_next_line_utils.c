/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:53:25 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/18 15:36:36 by ekotova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @param dest str to copy
 * @param src str from which copy
 * @param n copy n-bytes, but no more the len str
 * @return void*
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
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
 * but not more than str_len. Cuz in opposite case ft_memcpy
 * has undefined behavior. free str;
 *
 * @param str string with some data;
 * @param str_len len of the str.
 * @param new_len len of tail + space for new buf;
 * @return * char* ptr to new str with another size.
 */
char	*ft_realloc(char *str, size_t to_copy, size_t new_len)
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
	int	pos;

	pos = 0;
	while (pos < buf_len)
	{
		if (buf[pos] == '\n')
		{
			*is_line = 1;
			return (pos);
		}
		pos++;
	}
	*is_line = 0;
	return (pos);
}

void	reset_state(t_buf_stat *st)
{
	st->buf_pos = 0;
	st->buf_len = 0;
	st->is_line = 0;
}

int	ensure_line_capacity(t_buf_stat *st, int buf_len)
{
	char	*tmp;

	while (st->line_len + buf_len + BUFFER_SIZE + 2 > st->line_capacity)
	{
		st->line_capacity *= 2;
		tmp = ft_realloc(st->line, st->line_len, st->line_capacity);
		if (tmp == NULL)
		{
			free(st->line);
			st->line = NULL;
			return (0);
		}
		st->line = tmp;
	}
	return (1);
}
