/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_value_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:00:56 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/17 11:57:42 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	load_reg_link(t_corewar *cw, t_carriage *carr, int arg_n)
{
	unsigned char	reg_n;

	map_get(cw, 1, carr->pc, &reg_n);
	cw->args[arg_n] = reg_n;
	carriage_move(carr, 1);
}

void	load_reg(t_corewar *cw, t_carriage *carr, int arg_n)
{
	load_reg_link(cw, carr, arg_n);
	if (regnumber_contains(cw->args[arg_n]))
		cw->args[arg_n] = carr->rg[cw->args[arg_n] - 1];
}
