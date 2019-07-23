#include "ft_cw.h"

void	ft_carr_load_dir(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	carr->arg[arg_n] = ft_map_get_dword(cw, carr->pc);
	carr->pc += 4;
}

void	ft_carr_load_ind_link(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	carr->arg[arg_n] = ft_map_get_word(cw, carr->pc);
	carr->pc += 2;
}

void	ft_carr_load_ind(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	ft_carr_load_ind_link(cw, carr, arg_n);
	carr->arg[arg_n] = ft_map_get_dword(carr->arg[arg_n]);
}

void	ft_carr_load_reg_link(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	ft_carr_load_dir(cw, carr, arg_n);
}

void	ft_carr_load_reg(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	ft_carr_load_reg_link(cw, carr, arg_n);
	carr->arg[arg_n] = carr->rg[carr->arg[arg_n]];
}

void	ft_carr_load_value(t_corewar *cw, t_carriage *carr,
			int arg_n, char value_type)
{
	char lnk;
	char val;

	lnk = value_type & FT_LINK;
	val = (value_type << 6) >> 6;
	if (val == REG_CODE)
	{
		if (lnk)
			ft_carr_load_reg_link(cw, carr, arg_n);
		else
			ft_carr_load_reg(cw, carr, arg_n);
	}
	else if (val == DIR_CODE)
		ft_carr_load_dir(cw, carr, arg_n);
	else if (val == IND_CODE)
	{
		if (lnk)
			ft_carr_load_dir_link(cw, carr, arg_n);
		else
			ft_carr_load_dir(cw, carr, arg_n);
	}
		
}