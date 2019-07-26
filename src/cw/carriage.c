#include "ft_cw.h"

t_carriage		*ft_carriage_new(t_carriage **carrs, int player_id, int pos)
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

void			ft_carr_load_arg_types(t_corewar *cw, t_carriage *carr)
{
	if (carr->arg_types != NULL)
		free(carr->arg_types);
	carr->arg_types = ft_get_arg_types(ft_map_get_byte(cw, carr->pc));
	ft_carr_move(carr, 1);
}

void			ft_carr_move(t_carriage *carr, int move)
{
	move %= MEM_SIZE;
	if (move < 0)
		carr->pc += MEM_SIZE;
	carr->pc += move;
	carr->pc = carr->pc % MEM_SIZE;
}