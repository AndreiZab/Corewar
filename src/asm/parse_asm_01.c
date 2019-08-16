/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 19:22:09 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 19:27:30 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static void		ft_string_connection(char *dst)
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

int				ft_add_text(char *src, int i)
{
	int		j;
	char	*dst;

	j = 1;
	if (!(dst = ft_strnew(ft_strlen(src + ++i) + 1)))
		ft_error("NO_MEMORY");
	dst[0] = '\n';
	while (src[i] && src[i] != '\"')
		dst[j++] = src[i++];
	ft_string_connection(dst);
	if (src[i] == '\"' && i++)
		g_data->quotes++;
	while (src[i])
	{
		if (src[i] == '\"' && g_data->quotes++ && g_data->quotes > 2)
			ft_error("TOO_MANY_QUOTES");
		if ((g_data->quotes == 2 || g_data->quotes == 4) && src[i] != '\0'
			&& src[i] != ' ' && src[i] != '\t')
			ft_error("WRONG_SYMBOL_AFTER_QUOTES");
		i++;
	}
	free(dst);
	return (i);
}

static char		*ft_get_name_or_comment(char *src, int *i, char flag)
{
	int		j;
	char	*dst;

	j = 0;
	g_data->quotes = 0;
	if (!(dst = ft_strnew(ft_strlen(src + (*i)))))
		ft_error("NO_MEMORY");
	if (src[++(*i) - 1] == '\"')
		g_data->quotes++;
	while (src[*i] && src[*i] != '\"')
		dst[j++] = src[(*i)++];
	if (src[(*i)] == '\"' && (*i)++)
		g_data->quotes++;
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

static void		ft_check_quotes(char *str, int *i)
{
	while (str[*i] && str[*i] != '\"')
	{
		str[*i] == '\'' ? ft_error("WRONG_QUOTES") : 0;
		if (str[*i] != ' ' && str[*i] != '\t')
			ft_error("WRONG_SYMBOL_BEFORE_QUOTES");
		(*i)++;
	}
}

int				ft_find_name_or_comment(char *str, int i)
{
	if (str[i] == NAME_CMD_STRING[0] && !ft_strncmp(str + i,
			NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (g_data->name)
			ft_error("NAME_ALREADY_EXIST");
		i += ft_strlen(NAME_CMD_STRING);
		ft_check_quotes(str, &i);
		g_data->name = ft_get_name_or_comment(str, &i, 'n');
	}
	else if (str[i] == COMMENT_CMD_STRING[0] && !ft_strncmp(str + i,
			COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
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
