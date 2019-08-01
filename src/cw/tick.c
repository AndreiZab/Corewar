#include "ft_cw.h"

void	ft_do_command(t_corewar *cw, t_carriage *carr)
{
	//можно сократить до 1 строки
	t_comm_handler	*commh;

	commh = ft_commh_by_byte(cw, carr->command);
	commh->f(cw, carr);
}

void	ft_grab_command(t_corewar *cw, t_carriage *carr)
{
	t_comm_handler	*commh;

	carr->command = ft_map_get_byte(cw, carr->pc);
	carr->pc_comm = carr->pc;
	commh = ft_commh_by_byte(cw, carr->command);
	carr->preparing_ticks = commh->cycles;
}

int	ft_tick(t_corewar *cw)
{
	t_carriage	*carr;

	carr = cw->carriages;
	while (carr)
	{
		if ((carr->preparing_ticks)-- <= 0)
		{
			
			if (carr->command != 0)
				ft_do_command(cw, carr);
			ft_grab_command(cw, carr);
			--(carr->preparing_ticks);
		}
		carr = carr->next;
	}
	return (FT_OK);
}