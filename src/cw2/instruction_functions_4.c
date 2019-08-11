#include "corewar.h"

int		lldi_function(t_corewar *cw, t_carriage *carr)
{
	int		value;

	load_value(cw, carr, 0, cw->temp_types[0] | COREWAR_IDX);
	load_value(cw, carr, 1, cw->temp_types[1]);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		map_get(cw, 4, carr->pc_comm + cw->args[0] + cw->args[1], &value);
		carr->rg[cw->args[2] - 1] = value;
		carr->carry = (carr->rg[cw->args[2] - 1] == 0) ? 1 : 0;
	}
	return (COREWAR_STATUS_OK);	
}

int		lfork_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, DIR_CODE);
	return (carriage_copy(cw, carr, carr->pc_comm + cw->args[0]));	
}

int		aff_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, REG_CODE);
	if (cw->options & COREWAR_OPT_AFF)
		ft_putchar(cw->args[0]);
	return (COREWAR_STATUS_OK);	
}
