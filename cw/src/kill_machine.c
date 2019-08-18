/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_machine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:59:49 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:59:50 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		kill_carriages(t_corewar *cw)
{
	t_carriage	*carr;
	int			carr_counter;

	carr = cw->carrs;
	if (carr)
		carr_counter = carr->id;
	while (carr)
	{
		if (!carr->dead)
		{
			if (carr->live_cycle <= cw->cycle_to_die - cw->die_step
				|| cw->die_step <= 0)
			{
				carr->dead = 1;
				if (cw->log & COREWAR_OPT_LOG_DEATHS)
					print_carriage_death(cw, carr);
				--carr_counter;
			}
		}
		else
			--carr_counter;
		carr = carr->next;
	}
	return (carr_counter);
}

int		find_winner(t_corewar *cw)
{
	t_player	*pl;
	int			i;
	int			max_live;
	int			max_i;

	max_live = -1;
	i = -1;
	while (++i < cw->players_count)
	{
		pl = cw->players + i;
		if (max_live <= pl->live)
		{
			max_live = pl->live;
			max_i = i;
		}
	}
	return (max_i + 1);
}

void	calculate_next_die_cycle(t_corewar *cw)
{
	static int		checks = 0;

	if (cw->cycle_lives_counter >= NBR_LIVE)
	{
		cw->die_step -= CYCLE_DELTA;
		checks = 0;
	}
	else if (checks == MAX_CHECKS - 1)
	{
		cw->die_step -= CYCLE_DELTA;
		checks = 0;
	}
	else
		++checks;
	cw->cycle_to_die += (cw->die_step > 0) ? cw->die_step : 1;
	if (cw->log & COREWAR_OPT_LOG_CYCLES)
		print_die_step(cw);
	cw->cycle_lives_counter = 0;
}

int		kill_machine(t_corewar *cw)
{
	int		winner_id;

	if (kill_carriages(cw) == 0)
	{
		winner_id = find_winner(cw);
		cw->winner = cw->players + winner_id - 1;
		print_winner(cw, winner_id);
		return (COREWAR_STATUS_FINISH);
	}
	calculate_next_die_cycle(cw);
	return (COREWAR_STATUS_OK);
}
