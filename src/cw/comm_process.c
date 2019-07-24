#include "ft_cw.h"

//У всех функций сдвиг на 1, так как нужно покинуть байт команду.
//Вынести во внешнюю функцию!

void	ft_comm_live(t_corewar *cw, t_carriage *carr, int (*f)())
{
	t_player	*pl;

	ft_carr_move(carr, 1);
	ft_carr_load_dir(cw, carr, 0);
	carr->cycle_live = cw->cycle;
	pl = ft_player_by_id(cw->players, carr->arg[0]);
	pl->live = carr->cycle_live;
}

void	ft_comm_ld(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_arg_types(cw, carr);
	ft_carr_load_value(cw, carr, 0, carr->arg_types[0]);
	ft_carr_load_value(cw, carr, 1, REG_CODE);
	carr->rg[carr->arg[1]] = carr->arg[0];
	carr->carry = (carr->arg[0] == 0) ? 1 : 0;
}

// arg_types индекс 1 взят на основании мнения о том,
// что тип указывается в соответствии с номером аргумента
// Если для первого аргумента тип однозначен, неоднозначный тип второго аргумента все равно будет записан в следующую "ячейку"

void	ft_comm_st(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_arg_types(cw, carr);
	ft_carr_load_value(cw, carr, 0, REG_CODE);
	if (carr->arg_types[1] == REG_CODE)
	{
		ft_carr_load_value(cw, carr, 1, REG_CODE | FT_LINK);
		carr->rg[carr->arg[1]] = carr->arg[0];
	}
	else if (carr->arg_types[1] == IND_CODE)
	{
		ft_carr_load_value(cw, carr, 1, IND_CODE | FT_LINK);
		carr->arg[1] %= IDX_MOD;
		// - 10 = сдвиг к началу инструкции
		ft_carr_move(carr, -10);
		ft_map_set(cw, carr->pc + carr->arg[1], carr->arg[0]);
		ft_carr_move(carr, 10);
	}
}

void	ft_comm_add(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_value(cw, carr, 0, REG_CODE);
	ft_carr_load_value(cw, carr, 1, REG_CODE);
	ft_carr_load_value(cw, carr, 2, REG_CODE | FT_LINK);
	carr->rg[carr->arg[2]] = carr->rg[carr->arg[0]] + carr->rg[carr->arg[1]];
}

void	ft_comm_sub(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_value(cw, carr, 0, REG_CODE);
	ft_carr_load_value(cw, carr, 1, REG_CODE);
	ft_carr_load_value(cw, carr, 2, REG_CODE | FT_LINK);
	carr->rg[carr->arg[2]] = carr->rg[carr->arg[0]] - carr->rg[carr->arg[1]];
}

void	ft_comm_and(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_arg_types(cw, carr);
	ft_carr_load_value(cw, carr, 0, carr->arg_types[0]);
	ft_carr_load_value(cw, carr, 1, carr->arg_types[1]);
	ft_carr_load_value(cw, carr, 2, REG_CODE | FT_LINK);
	carr->rg[carr->arg[2]] = carr->arg[0] & carr->arg[1];
	carr->carry = carr->rg[carr->arg[2]] == 0 ? 1 : 0;
}

void	ft_comm_or(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_arg_types(cw, carr);
	ft_carr_load_value(cw, carr, 0, carr->arg_types[0]);
	ft_carr_load_value(cw, carr, 1, carr->arg_types[1]);
	ft_carr_load_value(cw, carr, 2, REG_CODE | FT_LINK);
	carr->rg[carr->arg[2]] = carr->arg[0] | carr->arg[1];
	carr->carry = carr->rg[carr->arg[2]] == 0 ? 1 : 0;
}

void	ft_comm_xor(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_arg_types(cw, carr);
	ft_carr_load_value(cw, carr, 0, carr->arg_types[0]);
	ft_carr_load_value(cw, carr, 1, carr->arg_types[1]);
	ft_carr_load_value(cw, carr, 2, REG_CODE | FT_LINK);
	carr->rg[carr->arg[2]] = carr->arg[0] ^ carr->arg[1];
	carr->carry = carr->rg[carr->arg[2]] == 0 ? 1 : 0;
}

//разобраться с and / or / xor
//move -4 обеспечивает корректность работы.
// live %val
// zjmp %-5 === -4 переместит указатель в начало инструкции (на zjmp)

void	ft_comm_zjmp(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_value(cw, carr, 0, DIR_CODE);
	if (carr->carry == 1)
	{
		ft_carr_move(carr, -4);
		ft_carr_move(carr, carr->arg[0]);
	}
}

void	ft_comm_ldi(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_arg_types(cw, carr);
	ft_carr_load_value(cw, carr, 0, carr->arg_types[0]);
	ft_carr_load_value(cw, carr, 1, carr->arg_types[1]);
}

void	ft_comm_fork(t_corewar *cw, t_carriage *carr, int (*f)())
{
	t_carriage *fork;

	ft_carr_move(carr, 1);
	ft_carr_load_value(cw, carr, 0, DIR_CODE);
	fork = ft_carriage_new(&(cw->carriages), carr->player_id,
				carr->arg[0] % IDX_MOD);
	ft_memcpy(fork->rg, carr->rg, sizeof(fork->rg));
	fork->carry = carr->carry;
	fork->cycle_live = carr->cycle_live;
	//и чото еще
}

void	ft_comm_lfork(t_corewar *cw, t_carriage *carr, int (*f)())
{
	t_carriage *fork;

	ft_carr_move(carr, 1);
	ft_carr_load_value(cw, carr, 0, DIR_CODE);
	fork = ft_carriage_new(&(cw->carriages), carr->player_id,
				carr->pc + carr->arg[0]);
	ft_memcpy(fork->rg, carr->rg, sizeof(fork->rg));
	fork->carry = carr->carry;
	fork->cycle_live = carr->cycle_live;
	//и чото еще
}

void	ft_comm_aff(t_corewar *cw, t_carriage *carr, int (*f)())
{
	ft_carr_move(carr, 1);
	ft_carr_load_value(cw, carr, 0, REG_CODE);
	if (cw->aff == 1)
		ft_putchar(carr->rg[carr->arg[0]]);
}