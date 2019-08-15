/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:14:10 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/15 21:35:01 by rhealitt         ###   ########.fr       */
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

int			ft_free_l(char *line)
{
	if (line)
		free(line);
	return (1);
}

void	ft_free_data(void)
{
	free(g_data->name);
	free(g_data->comment);
	free(g_data);
}

void	*ft_create(int fd, char *filename)
{
	t_data *data;

	g_data = 0;
	g_bytes = 0;
	g_buf = NULL;
	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		ft_error("NO_MEMORY");
	data->fd = fd;
	data->filename = filename;
	g_data = data;
	return (data);
}

char		*ft_get_name_or_comment(char *src, int *i, char flag)
{
	int j;
	char *dst;

	j = 0;
	g_data->quotes = 0;
	if (!(dst = ft_strnew(ft_strlen(src + (*i)))))
		ft_error("NO_MEMORY");
	if (src[++(*i) - 1] == '\"')
		g_data->quotes++;
	while (src[*i] && src[*i] != '\"')
		dst[j++] = src[(*i)++];
	if (src[(*i)] == '\"')
	{
		g_data->quotes++;
		(*i)++;
	}
	while (src[*i])
	{
		if (src[*i] == '\"' && g_data->quotes++ && g_data->quotes > 2)
			ft_error("TOO_MANY_QUOTES");
		if (g_data->quotes == 2 && src[*i] != ' ' && src[*i] != '\t')
			ft_error("WRONG_SYMBOL_AFTER_QUOTES");
		(*i)++;
	}
	if (g_data->quotes == 1 && flag == 'c')
		g_data->quotes = 3;
	return (dst);
}

void		ft_check_quotes(char *str, int *i)
{
	while (str[*i] && str[*i] != '\"')
	{
		str[*i] == '\'' ? ft_error("WRONG_QUOTES") : 0;
		if (str[*i] != ' ' && str[*i] != '\t')
			ft_error("WRONG_SYMBOL_BEFORE_QUOTES");
		(*i)++;
	}
}

int			ft_find_name_or_comment(char *str, int i)
{
	if (str[i] == NAME_CMD_STRING[0] && !ft_strncmp(str + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (g_data->name)
			ft_error("NAME_ALREADY_EXIST");
		i += ft_strlen(NAME_CMD_STRING);
		ft_check_quotes(str, &i);
		g_data->name = ft_get_name_or_comment(str, &i, 'n');

	}
	else if (str[i] == COMMENT_CMD_STRING[0] && !ft_strncmp(str + i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		if (g_data->comment)
			ft_error("COMMENT_ALREADY_EXIST");
		i += ft_strlen(COMMENT_CMD_STRING);
		ft_check_quotes(str, &i);
		g_data->comment = ft_get_name_or_comment(str, &i, 'c');
	}
	else
		ft_error("EXTRA_CHARACTER__NEED_NAME/COMMENT");
	return (i);
}

void		ft_string_connection(char *dst)
{
	char *tmp;

	if (g_data->quotes == 3)
	{
		tmp = ft_strjoin(g_data->comment, dst);
		free(g_data->comment);
		g_data->comment = tmp;
	}
	else if (g_data->quotes == 1)
	{
		tmp = ft_strjoin(g_data->name, dst);
		free(g_data->name);
		g_data->name = tmp;
	}
}

int			ft_add_text(char *src, int i)
{
	int j;
	char *dst;

	j = 1;
	if (!(dst = ft_strnew(ft_strlen(src + ++i) + 1)))
		ft_error("NO_MEMORY");
	dst[0] = '\n';
	while (src[i] && src[i] != '\"')
		dst[j++] = src[i++];
	ft_string_connection(dst);
	if (src[i] == '\"')
	{
		g_data->quotes++;
		i++;
	}
	while (src[i])
	{
		if (src[i] == '\"' && g_data->quotes++ && g_data->quotes > 2)
			ft_error("TOO_MANY_QUOTES");
		if ((g_data->quotes == 2 || g_data->quotes == 4) && src[i] != '\0' && src[i] != ' ' && src[i] != '\t')
			ft_error("WRONG_SYMBOL_AFTER_QUOTES");
		i++;
	}
	free(dst);
	return (i);
}

void		ft_row_is_data(char *str, int i)
{
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return;
		if (g_data->quotes == 1 || g_data->quotes == 3)
			 i = ft_add_text(str, i - 1);
		else
			i = ft_find_name_or_comment(str, i);
		if (str[i])
			i++;
		if (g_data->name && ft_strlen(g_data->name) > PROG_NAME_LENGTH)
			ft_error("NAME_TOO_LONG");
		if (g_data->comment && ft_strlen(g_data->comment) > COMMENT_LENGTH)
			ft_error("COMMENT_TOO_LONG");
	}
}

void		ft_check_row(char *str)
{
	if (!g_data->comment || !g_data->name || str[g_data->x] == '.' || g_data->quotes == 1 || g_data->quotes == 3)
		ft_row_is_data(str, g_data->x);
	else
		ft_row_is_code(str);
}

void		ft_revert_tokens(void)
{
	t_token *curr;
	t_token *prev;

	prev = NULL;
	if (g_data && g_data->tokens)
	{
		while (g_data->tokens)
		{
			curr = g_data->tokens->next;
			g_data->tokens->next = prev;
			g_data->tokens->prev = curr;
			prev = g_data->tokens;
			g_data->tokens = curr;
		}
		if (prev)
			g_data->tokens = prev;
	}
}

void		ft_read_champ(void)
{
	char *line;
	int err;

	line = NULL;
	while (ft_free_l(line) && (err = get_next_line(g_data->fd, &line)) > 0 && !(g_data->x = 0) && ++g_data->y)
	{
		if (g_data->tokens)
			ft_token_create(Line_feed);
		while (line[g_data->x] == ' ' || line[g_data->x] == '\t')
			g_data->x++;
		if (line[g_data->x] == COMMENT_CHAR || line[g_data->x] == ALT_COMMENT_CHAR)
			continue ;
		ft_check_row(line);
	}
	ft_token_create(EOF);
	ft_revert_tokens();
	if (g_data->quotes == 1 || g_data->quotes == 3)
		ft_error("ERROR_WITH_QUOTES");
	if (err == -1)
		ft_error("ERROR_READ_FILE");
	else if (!g_data->comment)
		ft_error("NO_COMMENT");
	else if (!g_data->name)
		ft_error("NO_NAME");
}

void	ft_asm(char *str)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) == -1)
		ft_error("FILE_NOT_FOUND");
	ft_create(fd, str);
	ft_read_champ();
	ft_syntax_champ();
	ft_compilation_champ();
	ft_write_bytes();
	if (close(fd) < 0)
		ft_error("CANT_CLOSE_FILE");
	ft_free_data();
}