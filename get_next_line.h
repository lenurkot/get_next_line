/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:37:07 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/18 15:36:39 by ekotova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# if BUFFER_SIZE < 1
#  error "BUFFER_SIZE SHOULD BE AT LEAST 1"
# endif
# include <stdlib.h>

typedef struct s_states
{
	char	buf[BUFFER_SIZE];
	int		buf_pos;
	int		buf_len;
	int		is_line;
	int		current_fd;
	char	*line;
	int		line_len;
	int		line_capacity;
}			t_buf_stat;

char		*get_next_line(int fd);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_realloc(char *str, size_t to_copy, size_t new_len);
int			is_new_line(char *buf, int buf_len, int *is_line);
void		reset_state(t_buf_stat *st);
int			ensure_line_capacity(t_buf_stat *st, int buf_len);

#endif
