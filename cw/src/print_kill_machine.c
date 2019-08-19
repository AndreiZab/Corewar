/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_kill_machine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:41:30 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:41:31 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_carriage_death(t_corewar *cw, t_carriage *carr)
{
	ft_putstr("Process ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, COREWAR_COLOR_CARRIAGE);
	ft_putnbr(carr->id);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr(" hasn't lived for ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, COREWAR_COLOR_CYCLE);
	ft_putnbr(cw->cycle - carr->live_cycle);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr(" cycles (CTD ");
	ft_putnbr(cw->die_step);
	ft_putstr(")\n");
}

void	print_die_step(t_corewar *cw)
{
	static int		prev_die_step = CYCLE_TO_DIE;

	if (cw->die_step == prev_die_step)
		return ;
	prev_die_step = cw->die_step;
	ft_putstr("Cycle to die is now ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, COREWAR_COLOR_DIE_STEP);
	ft_putnbr(cw->die_step);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putchar('\n');
}

void	print_winner(t_corewar *cw, int id)
{
	t_player *pl;

	pl = cw->players + id - 1;
	ft_putstr("Contestant ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, COREWAR_COLOR_PLAYER);
	ft_putnbr(id);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr(", \"");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, COREWAR_COLOR_PLAYER);
	ft_putstr(pl->name);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr("\", has won !\n");
}
