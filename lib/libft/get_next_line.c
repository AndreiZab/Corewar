/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 12:25:34 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/21 10:16:29 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int		get_next_line_get(t_fd_buffer *info, char *new_line_pos,
	char **line)
{
	char	*temp;
	size_t	pos;

	pos = (new_line_pos == NULL) ? info->length : new_line_pos - info->buff;
	if ((*line = ft_strnew(pos)) == NULL)
		return (-1);
	ft_memcpy(*line, info->buff, pos);
	if (pos == info->length)
	{
		free(info->buff);
		if ((info->buff = ft_strnew(1)) == NULL)
			return (-1);
		info->length = 0;
	}
	else
	{
		if ((temp = (char*)malloc(info->length - pos - 1)) == NULL)
			return (-1);
		ft_memcpy(temp, new_line_pos + 1, info->length - pos - 1);
		free(info->buff);
		info->buff = temp;
		info->length -= pos + 1;
	}
	return (1);
}

static int		get_next_line_read(t_fd_buffer *info, char **line)
{
	char	*buff[BUFF_SIZE];
	long	readed;
	char	*new_line_pos;

	new_line_pos = ft_memchr(info->buff, (int)'\n', info->length);
	if (new_line_pos != NULL)
		return (get_next_line_get(info, new_line_pos, line));
	while ((readed = read(info->fd, buff, BUFF_SIZE)) > 0)
	{
		if ((info->buff = ft_realloc(info->buff, info->length,
			info->length + readed)) == NULL)
			return (-1);
		ft_memcpy(info->buff + info->length, buff, readed);
		info->length += readed;
		new_line_pos = ft_memchr(info->buff, (int)'\n', info->length);
		if (new_line_pos != NULL)
			break ;
	}
	if (readed < 0)
		return (-1);
	if (readed == 0 && info->length == 0)
		return (0);
	return (get_next_line_get(info, new_line_pos, line));
}

int				get_next_line(const int fd, char **line)
{
	static t_fd_buffer	*start;
	t_fd_buffer			*current;

	if (fd < 0 || line == NULL)
		return (-1);
	current = start;
	while (current)
	{
		if (current->fd == fd)
			return (get_next_line_read(current, line));
		current = current->next;
	}
	current = (t_fd_buffer*)malloc(sizeof(t_fd_buffer));
	if ((current->buff = ft_strnew(1)) == NULL)
		return (-1);
	current->length = 0;
	current->fd = fd;
	current->next = start;
	start = current;
	return (get_next_line_read(current, line));
}
