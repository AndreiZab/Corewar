#include "ft_cw.h"

void	ft_comm_live(t_corewar *cw, t_carriage *carr, int (*f)())
{
	int id;

	carr->cycle_live = cw->cycle;
	id = ft_reverse_bytes();
	carr->pc += 5;
}