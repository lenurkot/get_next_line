/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekotova <ekotova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:37:07 by ekotova           #+#    #+#             */
/*   Updated: 2025/11/14 13:39:41 by ekotova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#if BUFFER_SIZE < 1
    #error "BUFFER_SIZE SHOULD BE AT LEAST 1"
#endif

char	*get_next_line(int fd);

#endif
