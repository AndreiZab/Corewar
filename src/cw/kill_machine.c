#include "ft_cw.h"

void	ft_find_winner(t_corewar *cw)
{
	t_player *pl;
	t_player *stored;

	pl = cw->players;
	while (pl)
	{
		if (pl->dead == 0)
		{
			stored = pl;
			break ;
		}
		else if (!stored || pl->dead > stored->dead)
		{
			stored = pl;
		}
		pl = pl->next;
	}
	ft_putstr("Contestant ");
	ft_putnbr(stored->id);
	ft_putstr(", \"");
	ft_putstr(stored->name);
	ft_putstr("\", has won !\n");
}

void	ft_player_kill(t_corewar *cw, int *play)
{
	static int	deaths = 0;
	t_player *pl;

	pl = cw->players;
	while (pl)
	{
		if (pl->dead == 0)
		{
			if (pl->live != 0)
				pl->live == 0;
			else
			{
				pl->dead = cw->cycle;
				++deaths;
				ft_putstr("kill: ");
				ft_putnbr(pl->id);
				ft_putchar('\n');
			}
		}
		pl = pl->next;
	}
	if (deaths >= cw->players_count)
	{
		ft_putstr("dead: ");
		ft_putnbr(cw->next_check);
		ft_putchar('\n');
		ft_find_winner(cw);
		*play = 0;
	}
}

void	ft_kill_machine(t_corewar *cw, int *play)
{
	static int	checks = 0;
	int			lives_counter;
	t_carriage	*carr;

	lives_counter = 0;
	carr = cw->carriages;
	while (carr)
	{
		if (carr->dead == 0)
		{
			if (carr->cycle_live == 0 || cw->cycles_to_die <= 0)
				carr->dead = 1;
			else
			{
				lives_counter += carr->cycle_live;
				carr->cycle_live = 0;
			}
		}
		carr = carr->next;
	}
	ft_player_kill(cw, play);
	if (lives_counter >= NBR_LIVE || ++checks == MAX_CHECKS)
	{
		cw->cycles_to_die -= CYCLE_DELTA;
		checks = 0;
	}
	cw->next_check += cw->cycles_to_die;
}