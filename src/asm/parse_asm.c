/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:14:10 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/12 12:55:03 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

int			ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

int			ft_free_l(char *line)
{
	if (line)
		free(line);
	return (1);
}

t_data	*ft_create(int fd)
{
	t_data *data;

	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		ft_error("NO_MEMORY", NULL);
	data->fd = fd;
	return (data);
}

char		*ft_get_name_or_comment(char *src, t_data *data)
{
	int i;
	int j;
	char *dst;

	i = 0;
	j = 0;
	while (src[i] && src[i] != '"')
		i++;
	dst = (char *)ft_memalloc(sizeof(ft_strlen(src + i)));
	i++;
	while (src[i] && src[i] != '"')
		dst[j++] = src[i++];
	if (src[i] != '"')
		ft_error("MISSING_CLOSING_QUOTES", data);
	dst[j] = '\0';
	return (dst);
}

void		ft_row_is_data(t_data *data, char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return ;
		if (str[i] == NAME_CMD_STRING[0] && !ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			if (data->name)
				ft_error("DOUBLE_NAME", data);
			else
				data->name = ft_get_name_or_comment(str + i, data);
		}
		if (str[i] == COMMENT_CMD_STRING[0] && !ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		{
			if (data->comment)
				ft_error("DOUBLE_COMMENT", data);
			else
				data->comment = ft_get_name_or_comment(str + i, data);
		}
	}

}

void		ft_check_row(t_data *data, char *str)
{
	if (!data->comment || !data->name)
		ft_row_is_data(data, str);
//	else if (1)
//		ft_row_is_code(data, str);
}

void		ft_read(t_data *data)
{
	char *line;
	int err;
	int i;

	line = NULL;
	while (ft_free_l(line) && (err = get_next_line(data->fd, &line)) > 0)
	{
		data->num_current_row++;
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i += (line[i] == ' ') ? 1 : 4;
		ft_check_row(data, line);
	}
	if (err == -1)
		ft_error("ERROR_READ_FILE", data);
	else if (!data->comment)
		ft_error("NO_COMMENT", data);
	else if (!data->name)
		ft_error("NO_NAME", data);
}

void	ft_asm(char *str)
{
	int fd;
	t_data *data;

	if ((fd = open(str, O_RDONLY)) == -1)
		ft_error("FILE_NOT_FOUND", NULL);
	data = ft_create(fd);
	ft_read(data);
	free(data->name);
	free(data->comment);
	free(data);
}