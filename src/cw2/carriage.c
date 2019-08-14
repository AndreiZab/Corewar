#include "corewar.h"

int		carriage_new(t_corewar *cw, unsigned char owner_id, int pos)
{
	t_carriage	*carr;

	if ((carr = (t_carriage*)ft_memalloc(sizeof(t_carriage))) == NULL)
		return (COREWAR_STATUS_FATAL);
	carr->owner_id = owner_id;
	if (REG_NUMBER > 0)
		carr->rg[0] = -owner_id;
	carr->pc = pos;
	carr->next = cw->carrs;
	cw->carrs = carr;
	if (carr->next != NULL)
		carr->id = carr->next->id + 1;
	else
		carr->id = 1;
	carriage_grab_instruction(cw, carr);
	return (COREWAR_STATUS_OK);
}

void	carriage_grab_instruction(t_corewar *cw, t_carriage *carr)
{
	char	*str;

	if (carr->pc_comm != carr->pc && cw->log & COREWAR_OPT_LOG_PC_MOVEMENTS)
	{
		ft_putstr("ADV ");
		ft_putnbr(carr->pc - carr->pc_comm);
		ft_putstr(" (0x");
		str = casting_uc_hex(carr->pc_comm, 4);
		ft_putstr(str);
		free(str);
		ft_putstr(" -> 0x");
		str = casting_uc_hex(carr->pc, 4);
		ft_putstr(str);
		free(str);
		ft_putstr(")\n");
	}
	carr->pc_comm = carr->pc;
	if ((carr->instruction = insts_find(cw, cw->map[carr->pc_comm])) != NULL)
		carr->sleep = carr->instruction->sleep;
	cw->players_map[carr->pc] = carr->owner_id;
}

void	carriage_move(t_carriage *carr, int move)
{
	carr->pc = map_normilize(carr->pc + move);

}

int		carriage_copy(t_corewar *cw, t_carriage *carr, int pos)
{
	t_carriage	*copy;

	if ((copy = (t_carriage*)ft_memalloc(sizeof(t_carriage))) == NULL)
		return (COREWAR_STATUS_FATAL);
	ft_memcpy(copy, carr, sizeof(t_carriage));
	copy->pc = map_normilize(pos);
	copy->next = cw->carrs;
	cw->carrs = copy;
	copy->id = copy->next->id + 1;
	carriage_grab_instruction(cw, copy);
	return (COREWAR_STATUS_OK);
}

void	carriage_move_by_types(t_corewar *cw, t_carriage *carr)
{
	int		i;

	i = -1;
	while (++i < carr->instruction->argc)
		load_value(cw, carr, 0, cw->temp_types[i]);
}