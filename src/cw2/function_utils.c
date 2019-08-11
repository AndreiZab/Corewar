#include "corewar.h"

void	load_types(t_corewar *cw, t_carriage *carr)
{
	unsigned char	type_byte;

	ft_bzero(cw->temp_types, sizeof(char) * 3);
	type_byte = cw->map[carr->pc];
	get_types(cw->temp_types, type_byte);
	carriage_move(carr, 1);
}

int		check_types(t_corewar *cw, t_carriage *carr)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		if (check_arg(carr->instruction->argt[i], cw->temp_types[i]) == 0)
			return (0);
	}
	return (1);
}