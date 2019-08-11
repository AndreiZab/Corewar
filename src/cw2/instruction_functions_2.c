#include "corewar.h"

int		add_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, REG_CODE);
	load_value(cw, carr, 1, REG_CODE);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		carr->rg[cw->args[2] - 1] = cw->args[0] + cw->args[1];
		carr->carry = (carr->rg[cw->args[2] - 1] == 0) ? 1 : 0;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);	
}

int		sub_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, REG_CODE);
	load_value(cw, carr, 1, REG_CODE);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		carr->rg[cw->args[2] - 1] = cw->args[0] - cw->args[1];
		carr->carry = (carr->rg[cw->args[2] - 1] == 0) ? 1 : 0;
	}
	return (COREWAR_STATUS_OK);	
}

int		and_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, cw->temp_types[0]);
	load_value(cw, carr, 1, cw->temp_types[1]);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		carr->rg[cw->args[2] - 1] = cw->args[0] & cw->args[1];
		carr->carry = carr->rg[cw->args[2] - 1] == 0 ? 1 : 0;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);	
}

int		or_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, cw->temp_types[0]);
	load_value(cw, carr, 1, cw->temp_types[1]);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		carr->rg[cw->args[2] - 1] = cw->args[0] | cw->args[1];
		carr->carry = carr->rg[cw->args[2] - 1] == 0 ? 1 : 0;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);	
}

int		xor_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, cw->temp_types[0]);
	load_value(cw, carr, 1, cw->temp_types[1]);
	load_value(cw, carr, 2, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[2]))
	{
		carr->rg[cw->args[2] - 1] = cw->args[0] ^ cw->args[1];
		carr->carry = carr->rg[cw->args[2] - 1] == 0 ? 1 : 0;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);	
}
