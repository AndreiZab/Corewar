/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_is_code_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:31:50 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/17 22:07:05 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int				ft_sep_search(char c)
{
	if (c == DIRECT_CHAR || c == SEPARATOR_CHAR || c == COMMENT_CHAR)
		return (1);
	if (c == '\0' || c == '\n' || c == '\"' || c == ' ' || c == '\t')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static void		ft_dup_label(void)
{
	char	*cont;
	t_label	*label;

	cont = g_data->labels->ptr->content;
	label = g_data->labels->next;
	while (label)
	{
		if (!ft_strcmp(cont, label->ptr->content))
			ft_error("DUPLICATES_LABEL");
		label = label->next;
	}
}

void			ft_create_label(void)
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
	ft_dup_label();
}

int				ft_register(char *line, int len)
{
	int	i;

	i = 0;
	if ((len == 2 || len == 3) && line[i++] == 'r')
	{
		while (ft_isdigit(line[i]) && i < len)
			i++;
		if (i == len && ft_atoi(line + 1) > 0)
			return (1);
		if (ft_atoi(line + 1) == 0 && line[i - 1] == '0' && i == len)
			return (1);
	}
	return (0);
}
