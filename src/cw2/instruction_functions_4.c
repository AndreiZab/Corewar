/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_functions_4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:05:02 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 15:59:56 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lldi_function(t_corewar *cw, t_carriage *carr)
{
	int		value;

	load_value(cw, carr, 0, cw->temp_types[0] | COREWAR_IDX);
	load_value(cw, carr, 1, cw->temp_types[1]);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		map_get(cw, 4, carr->pc_comm + cw->args[0] + cw->args[1], &value);
		carr->rg[cw->args[2] - 1] = value;
		carr->carry = (carr->rg[cw->args[2] - 1] == 0) ? 1 : 0;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);
}

int		lfork_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, DIR_CODE);
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		print_log_lfork(cw, carr);
	return (carriage_copy(cw, carr, carr->pc_comm + cw->args[0]));
}

int		aff_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, REG_CODE);
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	if (cw->options & COREWAR_OPT_AFF)
		ft_putchar(cw->args[0]);
	return (COREWAR_STATUS_OK);
}
