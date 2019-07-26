/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:11:02 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/26 17:08:14 by rhealitt         ###   ########.fr       */
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

void		ft_check_token(t_data *data)
{
	t_token *ptr;

	if (data && data->tokens)
	{;/*
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

void		ft_syntax_analysis(t_data *data)
{
	g_ops = ft_create_oper();
	ft_check_token(data);
}

