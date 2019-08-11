#include "corewar.h"

static int		check_sequence(t_corewar *cw)
{
	int		i;

	i = -1;
	while (++i < cw->players_count)
	{
		if (cw->players[i].set != 1)
			return (print_error("Bad champions ids", cw));
	}
	return (COREWAR_STATUS_OK);
}

int				check_players(t_corewar *cw)
{
	if (cw->players_count == 0)
		return (print_error("No one player loaded", cw));
	return (check_sequence(cw));
}

int				prepare_for_battle(t_corewar *cw)
{
	int			i;
	int			mem_part;
	t_player	*pl;

	mem_part = MEM_SIZE / cw->players_count;
	i = -1;
	while (++i < cw->players_count)
	{
		pl = cw->players + i;
		ft_memcpy(cw->map + (i * mem_part), pl->code, pl->size);
		ft_memset(cw->players_map + (i * mem_part), i + 1, pl->size);
		if ((carriage_new(cw, i + 1, i * mem_part)) != COREWAR_STATUS_OK)
			return (COREWAR_STATUS_FATAL);
	}
	return (COREWAR_STATUS_OK);
}

/*
** colors?
*/

static void		print_player(t_player *pl, int id, t_corewar *cw)
{
	(void)cw;
	ft_putstr("* Player ");
	ft_putnbr(id);
	ft_putstr(", weighing ");
	ft_putnbr(pl->size);
	ft_putstr(" bytes, \"");
	ft_putstr(pl->name);
	ft_putstr("\" (\"");
	ft_putstr(pl->comment);
	ft_putstr("\") !\n");
}

void			show_players(t_corewar *cw)
{
	int		i;

	ft_putstr("Introducing contestants...\n");
	i = -1;
	while (++i < cw->players_count)
		print_player(cw->players + i, i + 1, cw);
}