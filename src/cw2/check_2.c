/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:56:02 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 15:59:56 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		get_types(char types[3], char from)
{
	types[0] = (from & 0b11000000) >> 6;
	types[1] = (from & 0b00110000) >> 4;
	types[2] = (from & 0b00001100) >> 2;
}

int			get_size(t_instruction *inst, char type)
{
	if (type == REG_CODE)
		return (1);
	if (type == IND_CODE)
		return (IND_SIZE);
	if (type == DIR_CODE)
		return (inst->dir_size);
	return (0);
}

int			check_arg(char permission, char current)
{
	if ((permission & DISASM_REG && current == REG_CODE) ||
		(permission & DISASM_DIR && current == DIR_CODE) ||
		(permission & DISASM_IND && current == IND_CODE) ||
		(permission == 0 && current == 0))
		return (1);
	return (0);
}

static int	check_type(t_corewar *cw, t_player *pl, t_instruction *inst, int i)
{
	int		j;

	if (inst->type_byte)
	{
		if (++i < pl->size)
		{
			get_types(cw->temp_types, pl->code[i]);
			j = -1;
			while (++j < inst->argc)
				if (!check_arg(inst->argt[j], cw->temp_types[j]))
					return (print_error_file_inst(inst->name,
						"Wrong argument type", cw));
		}
		else
			return (print_error_file_inst(inst->name,
				"Champion's code was ended before type byte", cw));
	}
	else
	{
		cw->temp_types[0] = REG_CODE;
		if (inst->argt[0] != DISASM_REG)
			cw->temp_types[0] = (inst->argt[0] == DISASM_DIR) ?
				DIR_CODE : IND_CODE;
	}
	return (i);
}

int			check_instruction(t_corewar *cw, t_player *pl, t_instruction *inst,
				int i)
{
	int				arg1_size;
	int				arg2_size;
	int				arg3_size;

	i = check_type(cw, pl, inst, i);
	if (i < 0)
		return (-1);
	arg1_size = get_size(inst, cw->temp_types[0]);
	arg2_size = (inst->argc >= 2) ? get_size(inst, cw->temp_types[1]) : 0;
	arg3_size = (inst->argc >= 3) ? get_size(inst, cw->temp_types[2]) : 0;
	++i;
	if (i + arg1_size + arg2_size + arg3_size > pl->size)
		return (print_error_file_inst(inst->name, "No enough space", cw));
	return (i + arg1_size + arg2_size + arg3_size);
}
