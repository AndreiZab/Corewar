/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_value_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:00:42 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/17 11:57:42 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	load_ind_link(t_corewar *cw, t_carriage *carr, int arg_n)
{
	short int	ind;

	map_get(cw, 2, carr->pc, &ind);
	cw->args[arg_n] = ind;
	carriage_move(carr, 2);
}

void	load_ind(t_corewar *cw, t_carriage *carr, int arg_n, char idx)
{
	long int	dir4;
	short int	dir2;

	load_ind_link(cw, carr, arg_n);
	if (idx & COREWAR_IDX)
		cw->args[arg_n] %= IDX_MOD;
	if (carr->instruction->dir_size == 4)
	{
		map_get(cw, 4, carr->pc_comm + cw->args[arg_n], &dir4);
		cw->args[arg_n] = dir4;
	}
	else if (carr->instruction->dir_size == 2)
	{
		map_get(cw, 2, carr->pc_comm + cw->args[arg_n], &dir2);
		cw->args[arg_n] = dir2;
	}
}

void	load_dir(t_corewar *cw, t_carriage *carr, int arg_n)
{
	int				dir_size;
	long int		dir4;
	short int		dir2;

	dir_size = carr->instruction->dir_size;
	if (dir_size == 4)
	{
		map_get(cw, 4, carr->pc, &dir4);
		cw->args[arg_n] = dir4;
	}
	else if (dir_size == 2)
	{
		map_get(cw, 2, carr->pc, &dir2);
		cw->args[arg_n] = dir2;
	}
	carriage_move(carr, dir_size);
}

void	load_value(t_corewar *cw, t_carriage *carr, int arg_n, char val_type)
{
	char	val;
	char	link;

	val = (val_type & 0b00000011);
	link = (val_type & COREWAR_LINK);
	if (val == REG_CODE)
	{
		if (link)
			load_reg_link(cw, carr, arg_n);
		else
			load_reg(cw, carr, arg_n);
	}
	else if (val == IND_CODE)
	{
		if (link)
			load_ind_link(cw, carr, arg_n);
		else
			load_ind(cw, carr, arg_n, val_type);
	}
	else if (val == DIR_CODE)
		load_dir(cw, carr, arg_n);
}
