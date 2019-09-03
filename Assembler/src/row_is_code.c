/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_is_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:55:41 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/18 17:28:56 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"


//Стоит оптимизировать, осталась пара архаизмов
static void		ft_txt(char *line, t_type type)
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
		{
			if (ft_register(line + temp, g_data->x - temp))
				g_data->tokens->type = Register;
			else
				g_data->tokens->type = Instruction;
		}
	}
	else
		ft_error("ERROR_WITH_TEXT");
}

//На самом деле не только nbr, стоит переназвать(но не сейчас :D)
static void		ft_number(char *line, t_type type)
{
	int		temp;

	temp = g_data->x;
	if (line[g_data->x] == '-')
		g_data->x++;
	while (ft_isdigit(line[g_data->x]))
		g_data->x++;
	if ((g_data->x - temp) && (type == Direct
	|| ft_sep_search(line[g_data->x])))
	{
		ft_token_create(type);
		g_data->tokens->content = ft_strsub(line, temp, g_data->x - temp);
	}
	else if (type == Indirect)
	{
		g_data->x = temp;
		ft_txt(line, Indirect);
	}
	else
		ft_error("INVALID_NBR");
}

//Ищем совпадение символов из строк и из op.h
static void		ft_parse_token(char **line)
{
	char *str;

	str = *line;
	if (str[g_data->x] == SEPARATOR_CHAR && ++g_data->x)
		ft_token_create(Separator);
	else if (str[g_data->x] == DIRECT_CHAR && ++g_data->x)
	{
		if (str[g_data->x] == LABEL_CHAR && ++g_data->x)
			ft_txt(str, Direct_label);
		else
			ft_number(str, Direct);
	}
	else if (str[g_data->x] == LABEL_CHAR && ++g_data->x)
		ft_txt(str, Indirect_label);
	else
		ft_number(str, Indirect);
	*line = str;
}

// Будем итерироваться по всей строке и парсить нужные токены
void			ft_row_is_code(char *line)
{
	while (line[g_data->x])
	{
		while (line[g_data->x] == ' ' || line[g_data->x] == '\t')
			g_data->x++;
		if (line[g_data->x] == COMMENT_CHAR
		|| line[g_data->x] == ALT_COMMENT_CHAR)
			return ;
		if (line[g_data->x])
			ft_parse_token(&line);
	}
}
