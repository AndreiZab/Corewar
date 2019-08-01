#include "ft_cw.h"

void	ft_carr_load_dir(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	if (cw->dir_size == 4)	
		carr->arg[arg_n] = ft_map_get_dword(cw, carr->pc);
	else if (cw->dir_size == 2)
		carr->arg[arg_n] = ft_map_get_word(cw, carr->pc);
	carr->pc += cw->dir_size;
}

void	ft_carr_load_ind_link(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	
	carr->arg[arg_n] = ft_map_get_word(cw, carr->pc);
	carr->pc += 2;
}

void	ft_carr_load_ind(t_corewar *cw, t_carriage *carr,
			int arg_n, char idx)
{
	int		val;

	ft_carr_load_ind_link(cw, carr, arg_n);
	val = carr->arg[arg_n];
	if (idx)
		val %= IDX_MOD;
	if (cw->dir_size == 4)
		carr->arg[arg_n] = ft_map_get_dword(cw, carr->pc_comm + val);
	else if (cw->dir_size == 2)
		carr->arg[arg_n] = ft_map_get_word(cw, carr->pc_comm + val);
		
}

void	ft_carr_load_reg_link(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	carr->arg[arg_n] = ft_map_get_byte(cw, carr->pc);
	carr->pc += 1;
}

void	ft_carr_load_reg(t_corewar *cw, t_carriage *carr,
			int arg_n)
{
	ft_carr_load_reg_link(cw, carr, arg_n);
	if (ft_regnumber_contains(carr->arg[arg_n]))
		carr->arg[arg_n] = carr->rg[carr->arg[arg_n] - 1];
}

void	ft_carr_load_value(t_corewar *cw, t_carriage *carr,
			int arg_n, char value_type)
{
	char	lnk;
	char	val;
	char	idx_val;

	idx_val = value_type & FT_IDX_USE;
	lnk = value_type & FT_LINK;
	val = value_type & 0b00000011;
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
			ft_carr_load_ind_link(cw, carr, arg_n);
		else
			ft_carr_load_ind(cw, carr, arg_n, idx_val);
	}
		
}