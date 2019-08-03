/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:11:02 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/02 20:25:02 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

typedef struct		s_ops
{
	int				*command_nums;
	int				*count_of_args;
	int				*arg1_type;
	int				*arg2_type;
	int				*arg3_type;
	int				*arg_code_exists;
	int				*t_dir_coefs;
}					t_ops;

char		g_commands[REG_NUMBER][6] = {
		"live",
		"ld",
		"st",
		"add",
		"sub",
		"and",
		"or",
		"xor",
		"zjmp",
		"ldi",
		"sti",
		"fork",
		"lld",
		"lldi",
		"lfork",
		"aff"
};

int				g_arg_type_1[REG_NUMBER] = {
		T_DIRS,
		T_DIRS + T_INDS,
		T_REGS,
		T_REGS,
		T_REGS,
		T_REGS + T_DIRS + T_INDS,
		T_REGS + T_DIRS + T_INDS,
		T_REGS + T_DIRS + T_INDS,
		T_DIRS,
		T_REGS + T_DIRS + T_INDS,
		T_REGS,
		T_DIRS,
		T_DIRS + T_INDS,
		T_REGS + T_DIRS + T_INDS,
		T_DIRS,
		T_REGS
};

int				g_arg_type_2[REG_NUMBER] = {
		0,
		T_REGS,
		T_REGS + T_INDS,
		T_REGS,
		T_REGS,
		T_REGS + T_DIRS + T_INDS,
		T_REGS + T_DIRS + T_INDS,
		T_REGS + T_DIRS + T_INDS,
		0,
		T_REGS + T_DIRS,
		T_REGS + T_DIRS + T_INDS,
		0,
		T_REGS,
		T_REGS + T_DIRS,
		0,
		0
};

int				g_arg_type_3[REG_NUMBER] = {
		0,
		0,
		0,
		T_REGS,
		T_REGS,
		T_REGS,
		T_REGS,
		T_REGS,
		0,
		T_REGS,
		T_REGS + T_DIRS,
		0,
		0,
		T_REGS,
		0,
		0
};

t_ops		*g_ops = NULL;

size_t		g_label_num = 0;

/*
 *
 * ^		^
 * | GLOBAL |
 *
 */

int			ft_is_command(char *str)
{
	int i;

	i = 0;
	while (i <= REG_NUMBER)
	{
		if (!ft_strcmp(str, g_commands[i]))
			return (1);
		i++;
	}
	return (0);
}

void		ft_check_token(t_data *data)
{
	t_token *ptr;

	if (data && data->tokens)
	{
		;/*
		ptr = data->tokens;
		while (ptr->next)
			ptr = ptr->next;
		if (ptr->content[0] != '\n')
			ft_error("LAST_LINE_MUST_BE_EOL", data);
	Подумать как чекнуть последнюю линию(гнл не читает))
 			Хотелось бы это сделать без lseeck*/
	}
	else
		ft_error("NO_TOKENS", data);
}

t_label		*ft_create_label()
{
	t_label *label;

	if (!(label = (t_label *)ft_memalloc(sizeof(t_label))))
		ft_error("NO_MEMORY", NULL);
	label->next = NULL;
	label->line = 0;
	label->name = NULL;
	return (label);
}
t_label		*ft_labeladd_end(t_label *head, t_label *label)
{
	t_label *ptr;

	if (head && head->name == NULL)
		head = label;
	else if (label && head)
	{
		ptr = head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = label;
	}
	return (head);
}
t_label		*ft_parse_label(t_data *data)
{
	t_token *cur;
	t_label *label;
	t_label *head;

	head = ft_create_label();
	cur = data->tokens;
	while (cur)
	{
		if (cur->type == Label)
		{
			label = ft_create_label();
			label->line = cur->row;
			label->name = ft_strdup(cur->content);
			head = ft_labeladd_end(head, label);
		}
		cur = cur->next;
	}
	if (head && head->name)
		return (head);
	else
		return (NULL);

}
void		ft_syntax_analysis01(t_data *data)
{

}

void		ft_validate_all_code(t_data *data, t_token *ptr)
{
	while (ptr)
	{
		if (ptr->type == Label)
			ft_validate_label();
		else if (!data->processing_row && (ptr->type == Whitespace || ptr->type == Line_feed))
			continue ;
		else if (ptr->type == Command)
			ft_validate_command();
		else if (ft_find_arg())
			ft_error("ARGUMENTS_WITHOUT_A_COMMAND", data);
		else if (ft_add_content_in_row(data)) //124-129-131
			continue;
		else if (ptr->type == Separator && data->past_type && data->past_type == Separator)
			ft_error("EXTRA_SEPARATOR", data);
		else if (ft_sep_before_n(data))//86-93 - 95
			ft_error("SEPARATOR_BEFORE_NEWLINE", data);
		else if (ptr->type == Line_feed)
			ft_define(data);
		else if (ft_validate_label_arg(data))
			ft_error("LABEL_NOT_INITIALIZED", data);
		else if (ft_is_arg(data))
			ft_validate_arg(data); //71-74
		data->past_type = ptr->type; // унеси отсюда
		ptr = ptr->next;
	}
}

void		ft_syntax_analysis(t_data *data)
{

	ft_check_token(data);
//	g_ops = ft_create_oper();
	data->labels = ft_parse_label(data);
	ft_validate_all_code(data, data->tokens);

}

