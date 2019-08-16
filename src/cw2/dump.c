/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:58:09 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:58:11 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		dump_registers(t_carriage *carr)
{
	int rg_i;

	rg_i = -1;
	while (++rg_i < REG_NUMBER)
	{
		ft_putstr("\n\t\trg[");
		ft_putnbr(rg_i + 1);
		ft_putstr("] = ");
		ft_putnbr(carr->rg[rg_i]);
	}
}

void		dump_carriages_by_owner(t_corewar *cw, unsigned char owner_id)
{
	t_carriage	*carr;

	carr = cw->carrs;
	while (carr)
	{
		if (carr->owner_id == owner_id)
		{
			ft_putstr("\n\t== Position: ");
			ft_putnbr(carr->pc);
			ft_putstr(" ID: ");
			ft_putnbr(carr->id);
			ft_putstr((carr->carry) ? "\n\tCarry: Yes" : "\n\tCarry: No");
			ft_putstr("\n\tLast live instruction: ");
			ft_putnbr(carr->live_cycle);
			ft_putstr("\n\tRegisters:");
			dump_registers(carr);
		}
		carr = carr->next;
	}
}

void		dump_players(t_corewar *cw)
{
	t_player	*pl;
	int			i;

	i = -1;
	while (++i < cw->players_count)
	{
		pl = cw->players + i;
		ft_putstr("\n== Player ");
		ft_putnbr(i + 1);
		ft_putstr(", Champion: '");
		ft_putstr(pl->name);
		ft_putstr("'\nLast live instruction: ");
		ft_putnbr(pl->live);
		ft_putstr("\nLive carriages:");
		dump_carriages_by_owner(cw, i + 1);
	}
}

void		corewar_dump_info(t_corewar *cw)
{
	ft_putstr("=== DUMP INFO ===\nCycle: ");
	ft_putnbr(cw->cycle);
	dump_players(cw);
	ft_putchar('\n');
}

int			corewar_dump(t_corewar *cw)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % COREWAR_DUMP_COLUMNS == 0)
			print_address(cw, i);
		if (cw->options & COREWAR_OPT_COLORS)
			ft_setcolor(cc_current, (cw->players_map[i] >= 1 &&
				cw->players_map[i] <= 6) ? cw->players_map[i] : cc_default);
		print_map_byte(cw, i);
		if ((i + 1) % COREWAR_DUMP_COLUMNS == 0)
			ft_putchar('\n');
		if (cw->options & COREWAR_OPT_COLORS)
			ft_setcolor(cc_default, cc_default);
	}
	if (cw->options & COREWAR_OPT_DUMP_INFO)
		corewar_dump_info(cw);
	return (COREWAR_STATUS_OK);
}
