#include "corewar.h"

void	print_carriage_death(t_corewar *cw, t_carriage *carr)
{
	ft_putstr("Process ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_magenta);
	ft_putnbr(carr->id);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr(" hasn't lived for ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_magenta);
	ft_putnbr(cw->cycle - carr->live_cycle);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr(" cycles (CTD ");
	ft_putnbr(cw->die_step);
	ft_putstr(")\n");
}

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

int		kill_players(t_corewar *cw)
{
	t_player	*pl;
	int			i;
	int			killed;

	killed = 0;
	i = -1;
	while (++i < cw->players_count)
	{
		pl = cw->players + i;
		if (!pl->dead)
		{
			if (pl->live <= cw->cycle_to_die - cw->die_step)
			{
				pl->dead = 1;
				++killed;
			}
		}
		else
			++killed;
	}
	return (killed);
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


void	print_die_step(t_corewar *cw)
{
	static int		prev_die_step = -1;

	if (cw->die_step == prev_die_step)
		return ;
	prev_die_step = cw->die_step;
	ft_putstr("Cycle to die is now ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_yellow);
	ft_putnbr(cw->die_step);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putchar('\n');
}

void	calculate_next_die_cycle(t_corewar *cw)
{
	static int		checks = 0;

	if (cw->cycle_lives_counter >= NBR_LIVE)
	{
		cw->die_step -= CYCLE_DELTA;
		checks = 0;
	}
	else if (checks == MAX_CHECKS)
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

void	print_winner(t_corewar *cw, int id)
{
	t_player *pl;

	pl = cw->players + id - 1;
	ft_putstr("Contestant ");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_yellow);
	ft_putnbr(id);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr(", \"");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_yellow);
	ft_putstr(pl->name);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	ft_putstr("\", has won !\n");
}

int		kill_machine(t_corewar *cw)
{
	int		winner_id;

	if (kill_carriages(cw) == 0)
	{
		winner_id = find_winner(cw);
		print_winner(cw, winner_id);
		return (COREWAR_STATUS_FINISH);
	}
	kill_players(cw);
	calculate_next_die_cycle(cw);
	return (COREWAR_STATUS_OK);
}