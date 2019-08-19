/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_functions_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:04:27 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/18 15:52:18 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		zjmp_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, DIR_CODE);
	if (carr->carry == 1)
	{
		carriage_move(carr, -1 - carr->instruction->dir_size +
			cw->args[0] % IDX_MOD);
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		print_log_zjmp(cw, carr);
	return (COREWAR_STATUS_OK);
}

int		ldi_function(t_corewar *cw, t_carriage *carr)
{
	int		value;

	load_value(cw, carr, 0, cw->temp_types[0]);
	load_value(cw, carr, 1, cw->temp_types[1]);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		map_get(cw, 4, carr->pc_comm + (cw->args[0] +
			cw->args[1]) % IDX_MOD, &value);
		carr->rg[cw->args[2] - 1] = value;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		print_log_ldi(cw, carr);
	return (COREWAR_STATUS_OK);
}

int		sti_function(t_corewar *cw, t_carriage *carr)
{
	int		pos;

	load_value(cw, carr, 0, REG_CODE);
	load_value(cw, carr, 1, cw->temp_types[1] | COREWAR_IDX);
	load_value(cw, carr, 2, cw->temp_types[2]);
	pos = carr->pc_comm + (cw->args[1] + cw->args[2]) % IDX_MOD;
	map_set(cw, 4, pos, cw->args + 0);
	map_set_color(cw, pos, 4, carr->owner_id);
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		print_log_sti(cw, carr);
	return (COREWAR_STATUS_OK);
}

int		fork_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, DIR_CODE);
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		print_log_fork(cw, carr);
	return (carriage_copy(cw, carr, carr->pc_comm + (cw->args[0] % IDX_MOD)));
}

int		lld_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, cw->temp_types[0]);
	load_value(cw, carr, 1, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[1]))
	{
		carr->rg[cw->args[1] - 1] = cw->args[0];
		carr->carry = (cw->args[0] == 0) ? 1 : 0;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);
}
