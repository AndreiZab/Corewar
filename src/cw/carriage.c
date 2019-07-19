#include "ft_cw.h"

t_carriage	*ft_carriage_new(t_carriage **carrs, int player_id, int pos)
{
	t_carriage	*carr;

	if (carrs == NULL)
		return (NULL);
	carr = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	carr->player_id = player_id;
	carr->pc = pos;
	carr->next = *carrs;
	*carrs = carr;
	return (carr);
}