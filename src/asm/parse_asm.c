/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:14:10 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/13 17:20:50 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char*)malloc(sizeof(*dest) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
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

char		*ft_get_name_or_comment(char *src, t_data *data)
{
	int i;
	int j;
	char *dst;

	i = 0;
	j = 0;
	data->quotes = 0;
	while (src[i] && src[i] != '"')
		src[i] =='\'' ? ft_error("WRONG_QUOTES", data) : i++;
	dst = (char *)ft_memalloc(sizeof(ft_strlen(src + i)));
	if (src[++i - 1] == '"')
		data->quotes++;
	while (src[i] && src[i] != '"')
		src[i] =='\'' ? ft_error("WRONG_QUOTES", data) : (dst[j++] = src[i++]);
	while (src[i])
		if (src[i++] == '"' )
			data->quotes++;
	if (data->quotes > 2)
		ft_error("TOO_MANY_QUOTES", data);
	//if (data->quotes < 2)
//		ft_error("NO_ENOUGH_QUOTES", data);
	dst[j] = '\0';
	return (dst);
}

char		*ft_add_text(char *src, t_data *data)
{
	int i;
	int j;
	char *dst;

	i = 0;
	j = 0;
	dst = (char *)ft_memalloc(sizeof(ft_strlen(src + i)));
	while (src[i] && src[i] != '"')
		src[i] =='\'' ? ft_error("WRONG_QUOTES", data) : (dst[j++] = src[i++]);
	while (src[i])
		if (src[i++] == '"' )
			data->quotes++;
	if (data->quotes > 2)
		ft_error("TOO_MANY_QUOTES", data);
	dst[j] = '\0';
	return (dst);
}

void		ft_row_is_data(t_data *data, char *str, int i)
{
	while (str[++i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return;
		if (str[i] == NAME_CMD_STRING[0] && !ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			if (data->name)
				ft_error("NAME_ALREADY_EXIST", data);
			else
			{
				if (data->quotes == 1)
					data->name = ft_strjoin(data->name, ft_add_text(str, data));
				else
					data->name = ft_get_name_or_comment(str + i, data);
			}
		}
		else if (str[i] == COMMENT_CMD_STRING[0] &&
				   !ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		{
			if (data->comment)
				ft_error("COMMENT_ALREADY_EXIST", data);
			else
			{
				if (data->quotes == 1)
					data->comment = ft_strjoin(data->comment, ft_add_text(str, data));
				else
					data->comment = ft_get_name_or_comment(str + i, data);
			}
		}
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
	if (!data->comment || !data->name || str[i] == '.')
		ft_row_is_data(data, str, i - 1);
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
	ft_free_data(data);
}