#include "ft_cw.h"

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
	if (lives_counter >= NBR_LIVE || ++checks == MAX_CHECKS)
	{
		cw->cycles_to_die -= CYCLE_DELTA;
		checks = 0;
	}
}