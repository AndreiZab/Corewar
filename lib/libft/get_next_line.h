/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 12:25:57 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/21 10:28:21 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024
# include <string.h>

typedef struct	s_fd_buffer
{
	char				*buff;
	size_t				length;
	int					fd;
	struct s_fd_buffer	*next;
}				t_fd_buffer;

int				get_next_line(const int fd, char **line);

#endif
