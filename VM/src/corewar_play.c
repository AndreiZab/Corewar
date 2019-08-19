/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_play.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:57:50 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/18 15:52:17 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	permission_to_types(t_corewar *cw, t_instruction *inst)
{
	if (inst->argt[0] == DISASM_DIR)
		cw->temp_types[0] = DIR_CODE;
	else if (inst->argt[0] == DISASM_REG)
		cw->temp_types[0] = REG_CODE;
	else
		cw->temp_types[0] = IND_CODE;
}

int		execude_function(t_corewar *cw, t_carriage *carr)
{
	carriage_move(carr, 1);
	if (carr->instruction->type_byte)
	{
		load_types(cw, carr);
		if (!check_types(cw, carr) || !check_registers(cw, carr))
			carriage_move_by_types(cw, carr);
		else
		{
			if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
				print_log(cw, carr);
			return (carr->instruction->f(cw, carr));
		}
	}
	else
	{
		if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		{
			permission_to_types(cw, carr->instruction);
			print_log(cw, carr);
		}
		return (carr->instruction->f(cw, carr));
	}
	return (COREWAR_STATUS_OK);
}

void	do_carriage(t_corewar *cw, t_carriage *carr, int *status)
{
	if (carr->instruction != NULL)
	{
		*status = execude_function(cw, carr);
		if (carr->pc_comm != carr->pc &&
			cw->log & COREWAR_OPT_LOG_PC_MOVEMENTS)
			print_pc_movements(cw, carr);
		carr->instruction = NULL;
	}
	else
	{
		carriage_grab_instruction(cw, carr);
		if (carr->instruction == NULL)
			carriage_move(carr, 1);
	}
}

int		execude_carriages(t_corewar *cw)
{
	int				status;
	t_carriage		*carr;

	status = COREWAR_STATUS_OK;
	carr = cw->carrs;
	while (carr)
	{
		if (!carr->dead)
		{
			if (carr->sleep > 0)
				--carr->sleep;
			if (carr->sleep <= 1)
			{
				do_carriage(cw, carr, &status);
				if (status != COREWAR_STATUS_OK)
					break ;
			}
		}
		carr = carr->next;
	}
	return (status);
}

int		corewar_play(t_corewar *cw)
{
	int			status;

	status = COREWAR_STATUS_OK;
	while (status >= 0)
	{
		++(cw->cycle);
		if (cw->log & COREWAR_OPT_LOG_CYCLES)
			print_now_cycle(cw);
		status = execude_carriages(cw);
		if (cw->cycle == cw->cycle_to_die && status == COREWAR_STATUS_OK)
			status = kill_machine(cw);
		if (status != COREWAR_STATUS_OK)
			break ;
		if (cw->options & COREWAR_OPT_VISUALIZER)
			ft_vis_redraw(cw);
		if (cw->dump == (signed)cw->cycle)
		{
			status = corewar_dump(cw);
			break ;
		}
	}
	return (status);
}
