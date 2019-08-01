#include "ft_cw.h"

static int		ft_process_args(t_corewar *cw, int argc, char **argv)
{
	int				arg_i;
	int				err;

	ft_bandle_args(cw);
	arg_i = 0;
	err = FT_OK;
	while (err == FT_OK && ++arg_i < argc)
		err = ft_argh_do(cw, argc, argv, &arg_i);
	ft_argh_free(&cw->argh);
	ft_argh_free(&cw->argh_default);
	if (err == FT_OK && cw->players_count > 0)
	{
		ft_player_delete(&(cw->players));
		ft_set_ids(cw);
	}	
	return (err);
}

static int		ft_prepare_field(t_corewar *cw)
{
	int mem_part;
	int i;
	int	err;
	t_player	*pl;

	if (cw->players_count == 0)
		return (FT_NO_PLAYERS);
	if ((cw->map = (unsigned char*)ft_memalloc(MEM_SIZE)) == NULL)
		return (FT_MEMORY);
	mem_part = MEM_SIZE / cw->players_count;
	i = 0;
	while (++i <= cw->players_count)
	{
		pl = ft_player_by_id(cw->players, i);
		ft_memcpy(cw->map + (i - 1) * mem_part, pl->exe, pl->exe_size);
		ft_carriage_new(&(cw->carriages), -i, (i - 1) * mem_part);
	}
	cw->cycles_to_die = CYCLE_TO_DIE;
	if (cw->v)
	{
		/*return (ft_vis_init(cw))*/;
	}
	return (FT_OK);
}

static int		ft_play(t_corewar *cw)
{
	int play;

	ft_bandle_commands(cw);
	ft_show_players(cw);
	play = 1;
	cw->next_check = CYCLE_TO_DIE;
	while (play)
	{
		ft_tick(cw);
		if (cw->next_check == cw->cycle)
		{
			ft_kill_machine(cw, &play);
		}
		//if (cw->v)
		//	ft_vis_redraw(cw);
		if (cw->dump_mode == 1 && cw->dump_cycle == cw->cycle)
		{
			ft_show_dump(cw);
			break ;
		}
		++(cw->cycle);
	}
	return (FT_OK);
}

int				main(int argc, char **argv)
{
	t_corewar	*cw;
	int			err;

	cw = ft_cw_alloc(&err);
	err == FT_OK ? err = ft_process_args(cw, argc, argv) : 0;
	err == FT_OK ? err = ft_prepare_field(cw) : 0;
	err == FT_OK ? err = ft_play(cw) : 0;
	//ft_output(&cw);
	ft_cw_free(&cw);
	return (0);
}