/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:01:23 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/17 11:57:42 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		check_sequence(t_corewar *cw)
{
	int		i;

	i = -1;
	while (++i < cw->players_count)
	{
		if (cw->players[i].set != 1)
			return (print_error("Bad champions ids", cw));
	}
	return (COREWAR_STATUS_OK);
}

int				check_players(t_corewar *cw)
{
	if (cw->players_count == 0)
		return (print_error("No one player loaded", cw));
	return (check_sequence(cw));
}

int				prepare_for_battle(t_corewar *cw)
{
	int			i;
	int			mem_part;
	t_player	*pl;

	mem_part = MEM_SIZE / cw->players_count;
	i = -1;
	while (++i < cw->players_count)
	{
		pl = cw->players + i;
		ft_memcpy(cw->map + (i * mem_part), pl->code, pl->size);
		map_set_color(cw, (i * mem_part), pl->size, i + 1);
		if ((carriage_new(cw, i + 1, i * mem_part)) != COREWAR_STATUS_OK)
			return (COREWAR_STATUS_FATAL);
	}
	return (COREWAR_STATUS_OK);
}

/*
** colors?
*/

static void		print_player(t_player *pl, int id, t_corewar *cw)
{
	ft_putstr("* Player ");
	print_col_nbr(cw, id, COREWAR_COLOR_PLAYER);
	ft_putstr(", weighing ");
	ft_putnbr(pl->size);
	ft_putstr(" bytes, \"");
	print_col_str(cw, pl->name, COREWAR_COLOR_PLAYER);
	ft_putstr("\" (\"");
	print_col_str(cw, pl->comment, COREWAR_COLOR_PLAYER);
	ft_putstr("\") !\n");
}

void			show_players(t_corewar *cw)
{
	int		i;

	ft_putstr("Introducing contestants...\n");
	i = -1;
	while (++i < cw->players_count)
		print_player(cw->players + i, i + 1, cw);
}
