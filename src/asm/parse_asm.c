/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:14:10 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/14 20:05:11 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_asm.h"
#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char*)ft_memalloc(sizeof(*dest) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

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

void	ft_free_data(t_data *data)
{
	free(data->name);
	free(data->comment);
	free(data);
}

t_data	*ft_create(int fd)
{
	t_data *data;

	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		ft_error("NO_MEMORY", NULL);
	data->fd = fd;
	return (data);
}

char		*ft_get_name_or_comment(char *src, t_data *data, int *i, char flag)
{
	int j;
	char *dst;

	j = 0;
	data->quotes = 0;
	dst = (char *)ft_memalloc(sizeof(ft_strlen(src + (*i)) + 1));
	if (src[++(*i) - 1] == '"')
		data->quotes++;
	while (src[*i] && src[*i] != '"')
		dst[j++] = src[(*i)++];
	if (src[*i] == '"')
		data->quotes++;
	while (src[*i])
	{
		(*i)++;
		if (src[*i] == '"' && data->quotes++ && data->quotes > 2)
			ft_error("TOO_MANY_QUOTES", data);
		if (data->quotes == 2 && src[*i] != '\0' && src[*i] != ' ' && src[*i] != '\t')
			ft_error("WRONG_SYMBOL_AFTER_QUOTES", data);
	}
	if (data->quotes == 1 && flag == 'c')
		data->quotes = 3;
	return (dst);
}

int		ft_find_name_or_comment(char *str, t_data *data, int i)
{
	if (str[i] == NAME_CMD_STRING[0] && !ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (data->name)
			ft_error("NAME_ALREADY_EXIST", data);
		i += ft_strlen(NAME_CMD_STRING);
		while (str[i] && str[i] != '"')
		{
			str[i] == '\'' ? ft_error("WRONG_QUOTES", data) : 0;
			if (str[i] != ' ' && str[i] != '\t')
				ft_error("WRONG_SYMBOL_BEFORE_QUOTES", data);
			i++;
		}
		data->name = ft_get_name_or_comment(str, data, &i, 'n');

	}
	else if (str[i] == COMMENT_CMD_STRING[0] && !ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		if (data->comment)
			ft_error("COMMENT_ALREADY_EXIST", data);
		i += ft_strlen(COMMENT_CMD_STRING);
		while (str[i] && str[i] != '"')
		{
			str[i] == '\'' ? ft_error("WRONG_QUOTES", data) : 0;
			if (str[i] != ' ' && str[i] != '\t')
				ft_error("WRONG_SYMBOL_BEFORE_QUOTES", data);
			i++;
		}
		data->comment = ft_get_name_or_comment(str, data, &i, 'c');
	}
	return (i);
}

int		ft_add_text(char *src, t_data *data, int i)
{
	int j;
	char *dst;

	j = 1;
	dst = (char *)ft_memalloc(sizeof(ft_strlen(src + i) + 3));
	dst[0] = '\n';
	while (src[++i] && src[i] != '"')
		dst[j++] = src[i];
	if (data->quotes == 3)
		data->comment = ft_strjoin(data->comment, dst);
	else if (data->quotes == 1)
		data->name = ft_strjoin(data->name, dst);
	if (src[i] == '"')
		data->quotes++;
	while (src[i++])
	{
		if (src[i] == '"' && data->quotes++ && data->quotes > 2)
			ft_error("TOO_MANY_QUOTES", data);
		if (data->quotes == 2 && src[i] != '\0' && src[i] != ' ' && src[i] != '\t')
			ft_error("WRONG_SYMBOL_AFTER_QUOTES", data);
	}
	free(dst);
	return (i);
}

void		ft_row_is_data(t_data *data, char *str, int i)
{
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return;
		if (data->quotes == 1 || data->quotes == 3)
			i = ft_add_text(str, data, i - 1);
		else
			i = ft_find_name_or_comment(str, data, i);
		if (str[i])
			i++;
	}
}

void		ft_row_is_code (t_data *data, char *str, int i)
{
	while (str[++i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return ;
	}

}

void		ft_check_row(t_data *data, char *str, int i)
{
	if (!data->comment || !data->name || str[i] == '.' || data->quotes == 1 || data->quotes == 3)
		ft_row_is_data(data, str, i);
	else
		ft_row_is_code(data, str, i - 1);
}

void		ft_read(t_data *data)
{
	char *line;
	int err;
	int i;

	line = NULL;
	while (ft_free_l(line) && (err = get_next_line(data->fd, &line)) > 0)
	{
		data->count_char += ft_strlen(line);
		data->num_current_row++;
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		ft_check_row(data, line, i);
	}
	if (data->quotes == 1 || data->quotes == 3)
		ft_error("ERROR_WITH_QUOTES", NULL);
	if (err == -1)
		ft_error("ERROR_READ_FILE", NULL);
	else if (!data->comment)
		ft_error("NO_COMMENT", NULL);
	else if (!data->name)
		ft_error("NO_NAME", NULL);
}

void	ft_asm(char *str)
{
	int fd;
	t_data *data;

	if ((fd = open(str, O_RDONLY)) == -1)
		ft_error("FILE_NOT_FOUND", NULL);
	data = ft_create(fd);
	ft_read(data);
	ft_free_data(data);
}