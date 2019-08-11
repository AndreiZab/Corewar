#include "corewar.h"

void	print_live(t_corewar *cw, int player_id)
{
	if (cw->log & COREWAR_OPT_LOG_ORIGINAL)
	{
		ft_putstr("Player ");
		ft_putnbr(player_id);
		ft_putstr(" (");
		ft_putstr(cw->players[player_id - 1].name);
		ft_putstr(") is said to be alive\n");
	}
	else
	{
		ft_putstr("A process shows that player ");
		ft_putnbr(player_id);
		ft_putstr(" (");
		ft_putstr(cw->players[player_id - 1].name);
		ft_putstr(") is alive\n");
	}
}

int		live_function(t_corewar *cw, t_carriage *carr)
{
	carr->live_cycle = cw->cycle;
	++(carr->lives);
	++(cw->cycle_lives_counter);
	load_dir(cw, carr, 0);
	cw->args[0] *= -1;
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	if (1 <= cw->args[0] && cw->args[0] <= cw->players_count)
	{
		cw->players[cw->args[0] - 1].live = cw->cycle;
		if (cw->log & COREWAR_OPT_LOG_LIVES)
			print_live(cw, cw->args[0]);
	}
	return (COREWAR_STATUS_OK);	
}

int		ld_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, cw->temp_types[0] | COREWAR_IDX);
	load_value(cw, carr, 1, REG_CODE | COREWAR_LINK);
	if (regnumber_contains(cw->args[1]))
	{
		carr->rg[cw->args[1] - 1] = cw->args[0];
		carr->carry = (cw->args[0] == 0) ? 1 : 0;
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);	
}

int		st_function(t_corewar *cw, t_carriage *carr)
{
	load_value(cw, carr, 0, REG_CODE);
	if (cw->temp_types[1] == REG_CODE)
	{
		load_value(cw, carr, 1, REG_CODE | COREWAR_LINK);
		if (regnumber_contains(cw->args[1]))
			carr->rg[cw->args[1] - 1] = cw->args[0];
	}
	else if (cw->temp_types[1] == IND_CODE)
	{
		load_value(cw, carr, 1, IND_CODE | COREWAR_LINK);
		cw->args[1] %= IDX_MOD;
		map_set(cw, 4, carr->pc_comm + cw->args[1] % IDX_MOD, cw->args + 0);
		map_set_color(cw, carr->pc_comm + cw->args[1] % IDX_MOD, 4,
			carr->owner_id);
	}
	if (cw->log & COREWAR_OPT_LOG_OPERATIONS)
		ft_putchar('\n');
	return (COREWAR_STATUS_OK);	
}
