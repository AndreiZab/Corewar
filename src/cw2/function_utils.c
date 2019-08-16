/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:59:05 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 15:59:57 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	load_types(t_corewar *cw, t_carriage *carr)
{
	unsigned char	type_byte;

	ft_bzero(cw->temp_types, sizeof(char) * 3);
	type_byte = cw->map[carr->pc];
	get_types(cw->temp_types, type_byte);
	carriage_move(carr, 1);
}

int		check_types(t_corewar *cw, t_carriage *carr)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		if (check_arg(carr->instruction->argt[i], cw->temp_types[i]) == 0)
			return (0);
	}
	return (1);
}

int		check_registers(t_corewar *cw, t_carriage *carr)
{
	int				i;
	int				offset;
	unsigned char	reg_n;

	offset = 2;
	i = -1;
	while (++i < carr->instruction->argc)
	{
		if (cw->temp_types[i] == REG_CODE)
		{
			map_get(cw, 1, carr->pc_comm + offset, &reg_n);
			if (!(regnumber_contains(reg_n)) &&
				carr->instruction->argt[i] & DISASM_LINK)
				return (0);
		}
		else if (cw->temp_types[i] == DIR_CODE)
			offset += carr->instruction->dir_size;
		else if (cw->temp_types[i] == IND_CODE)
			offset += IND_SIZE;
	}
	return (1);
}
