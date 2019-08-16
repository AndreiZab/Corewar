/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_is_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:55:41 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 14:33:13 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int 	ft_sep_search(char c)
{
	if (c == DIRECT_CHAR || c == SEPARATOR_CHAR || c == COMMENT_CHAR)
		return (1);
	if (c == '\0' || c == '\n' || c == '\"' || c == ' ' || c == '\t')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void		ft_token_create(t_type type)
{
	t_token	*token;
	if (!(token = (t_token*)ft_memalloc(sizeof(t_token))))
		ft_error("NO_MEMORY");
	token->x = g_data->x;
	token->y = g_data->y;
	token->type = type;
	if (g_data->tokens)
		g_data->tokens->prev = token;
	token->next = g_data->tokens;
	g_data->tokens = token;
}

void		ft_dup_lable(void)
{
	char	*cont;
	t_label	*lable;

	cont = g_data->labels->ptr->content;
	lable = g_data->labels->next;
	while (lable)
	{
		if (!ft_strcmp(cont, lable->ptr->content))
			ft_error("DUPLICATES_LABEL");
		lable = lable->next;
	}
}

void		ft_create_label(void)
{
	t_label	*label;

	if (!(label = (t_label*)ft_memalloc(sizeof(t_label))))
		ft_error("NO_MEMORY");
	g_data->x++;
	g_data->tokens->type = Label;
	label->ptr = g_data->tokens;
	if (g_data->labels)
		g_data->labels->next = label;
	label->prev = g_data->labels;
	g_data->labels = label;
	ft_dup_lable();
}

int	is_reg(char *line, int len)
{
	int	i;

	i = 0;
	if ((len == 2 || len == 3) && line[i++] == 'r')
	{
		while (ft_isdigit(line[i]) && i < len)
			i++;
		if (i == len && ft_atoi(line + 1) > 0)
			return (1);
	}
	return (0);
}

static void	ft_get_txt(char *line, t_type type)
{
	int temp;

	temp = g_data->x;
	ft_token_create(type);
	while (line[g_data->x] && ft_strchr(LABEL_CHARS, line[g_data->x]))
		g_data->x++;
	g_data->tokens->content = ft_strsub(line, temp, g_data->x - temp);
	if ((g_data->x - temp) && line[g_data->x] == LABEL_CHAR)
		ft_create_label();
	else if ((g_data->x - temp) && ft_sep_search(line[g_data->x]))
	{
		if (type == Indirect)
			g_data->tokens->type = (is_reg(line + temp, g_data->x - temp)) ? Register : Instruction;
	}
	else
		ft_error("ERROR_WITH_TEXT");
}

static void	ft_direct_number(char *line)
{
	int		temp;

	temp = g_data->x;
	if (line[g_data->x] == '-' || line[g_data->x] == '+' )
		g_data->x++;
	while (ft_isdigit(line[g_data->x]))
		g_data->x++;
	if (g_data->x - temp)
	{
		ft_token_create(Direct);
		g_data->tokens->content = ft_strsub(line, temp, g_data->x - temp);
	}
	else
		ft_error("INVALID_DIRECT");
}

void		ft_indirect_number(char *line)
{
	int temp;

	temp = g_data->x;
	if (line[g_data->x] == '-' || line[g_data->x] == '+')
		g_data->x++;
	while (ft_isdigit(line[g_data->x]))
		g_data->x++;
	if ((g_data->x - temp) && (line[g_data->x] == DIRECT_CHAR || line[g_data->x] == SEPARATOR_CHAR))
	{
		ft_token_create(Indirect);
		g_data->tokens->content = ft_strsub(line, temp, g_data->x - temp);
	}
	else
	{
		g_data->x = temp;
		ft_get_txt(line, Indirect);
	}
}

void		ft_parse_token(char **line)
{
	char *str;
	str = *line;
	if (str[g_data->x] == SEPARATOR_CHAR && ++g_data->x)
		ft_token_create(Separator);
	else if (str[g_data->x] == '.' && ++g_data->x)
		ft_get_txt(str, Command);
	else if (str[g_data->x] == DIRECT_CHAR && ++g_data->x)
	{
		if (str[g_data->x] == LABEL_CHAR && ++g_data->x)
			ft_get_txt(str, Direct_label);
		else
			ft_direct_number(str);
	}
	else if (str[g_data->x] == LABEL_CHAR && ++g_data->x)
		ft_get_txt(str, Indirect_label);
	else
		ft_indirect_number(str);
	*line = str;
}

void		ft_row_is_code (char *line)
{
	while (line[g_data->x])
	{
		while (line[g_data->x] == ' ' || line[g_data->x] == '\t')
			g_data->x++;
		if (line[g_data->x] == COMMENT_CHAR || line[g_data->x] == ALT_COMMENT_CHAR)
			return ;
		if (line[g_data->x])
			ft_parse_token(&line);
	}
}
