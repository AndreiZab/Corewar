/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:53:39 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:53:41 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		carriage_new(t_corewar *cw, unsigned char owner_id, int pos)
{
	t_carriage	*carr;

	if ((carr = (t_carriage*)ft_memalloc(sizeof(t_carriage))) == NULL)
		return (COREWAR_STATUS_FATAL);
	carr->owner_id = owner_id;
	if (REG_NUMBER > 0)
		carr->rg[0] = -owner_id;
	carr->pc = pos;
	carr->next = cw->carrs;
	cw->carrs = carr;
	if (carr->next != NULL)
		carr->id = carr->next->id + 1;
	else
		carr->id = 1;
	carr->instruction = NULL;
	return (COREWAR_STATUS_OK);
}

void	carriage_grab_instruction(t_corewar *cw, t_carriage *carr)
{
	carr->pc_comm = carr->pc;
	if ((carr->instruction = insts_find(cw, cw->map[carr->pc_comm])) != NULL)
		carr->sleep = carr->instruction->sleep;
	cw->players_map[carr->pc] = carr->owner_id;
}

void	carriage_move(t_carriage *carr, int move)
{
	carr->pc = map_normilize(carr->pc + move);
}

int		carriage_copy(t_corewar *cw, t_carriage *carr, int pos)
{
	t_carriage	*copy;

	if ((copy = (t_carriage*)ft_memalloc(sizeof(t_carriage))) == NULL)
		return (COREWAR_STATUS_FATAL);
	ft_memcpy(copy, carr, sizeof(t_carriage));
	copy->pc = map_normilize(pos);
	copy->pc_comm = copy->pc;
	copy->next = cw->carrs;
	cw->carrs = copy;
	copy->id = copy->next->id + 1;
	copy->instruction = NULL;
	return (COREWAR_STATUS_OK);
}

void	carriage_move_by_types(t_corewar *cw, t_carriage *carr)
{
	int		i;
	int		step;

	i = -1;
	step = 0;
	while (++i < carr->instruction->argc)
		step += get_size(carr->instruction, cw->temp_types[i]);
	carriage_move(carr, step);
}
