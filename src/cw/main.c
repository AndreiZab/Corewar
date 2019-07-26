#include "ft_cw.h"

static t_corewar *ft_cw_alloc(int *err)
{
	t_corewar *cw;

	if ((cw = (t_corewar*)ft_memalloc(sizeof(t_corewar))) == NULL)
	{
		*err = FT_MEMORY;
		return (NULL);
	}
	if (ft_player_new(&cw->players) == NULL)
	{
		free(cw);
		*err = FT_MEMORY;
		return (NULL);
	}
	*err = FT_OK;
	return (cw);
}

static int		ft_process_args(t_corewar *cw, int argc, char **argv)
{
	int				arg_i;
	int				err;

	cw->argh = NULL;
	cw->argh_default = NULL;
	ft_argh_add(&(cw->argh), "-n", ft_process_flag_n); // Обработка флагов
	ft_argh_add(&(cw->argh), "-v", ft_process_flag_v);
	ft_argh_add(&(cw->argh), "-a", ft_process_flag_a);
	ft_argh_add(&(cw->argh), "-dump", ft_process_flag_dump);
	ft_argh_add(&(cw->argh_default), NULL, ft_process_file); // Обработка названий файлов
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
	if (cw->v)
	{
		/*return (ft_vis_init(cw))*/;
	}
	return (FT_OK);
}

static void		ft_info(t_corewar *cw) //DEBUG FUNCTION
{
	t_player	*player;

	ft_putstr("Players(");
	ft_putnbr(cw->players_count);
	ft_putstr("):\n");
	player = cw->players;
	while (player)
	{
		ft_putstr("Id: ");
		ft_putnbr(player->id);
		ft_putstr("\nName: ");
		ft_putstr(player->name);
		ft_putstr("\nComment: ");
		ft_putstr(player->comment);
		ft_putstr("\nMem size: ");
		ft_putnbr(player->exe_size);
		ft_putstr("\nLive: ");
		ft_putnbr(player->live);
		ft_putstr("\n\n");
		player = player->next;
	}
}

static int		ft_play(t_corewar *cw)
{
	int play;
	int tick;

	ft_commh_add(&(cw->commh), 1, 10, ft_comm_live);
	ft_commh_add(&(cw->commh), 2, 5, ft_comm_ld);
	ft_commh_add(&(cw->commh), 3, 5, ft_comm_st);
	ft_commh_add(&(cw->commh), 4, 10, ft_comm_add);
	ft_commh_add(&(cw->commh), 5, 10, ft_comm_sub);
	ft_commh_add(&(cw->commh), 6, 6, ft_comm_and);
	ft_commh_add(&(cw->commh), 7, 6, ft_comm_or);
	ft_commh_add(&(cw->commh), 8, 6, ft_comm_xor);
	ft_commh_add(&(cw->commh), 9, 20, ft_comm_zjmp);
	// ft_commh_add(&(cw->commh), 10, 25, ft_comm_process_ldi);
	// ft_commh_add(&(cw->commh), 11, 25, ft_comm_process_sti);
	// ft_commh_add(&(cw->commh), 12, 800, ft_comm_process_fork);
	// ft_commh_add(&(cw->commh), 13, 10, ft_comm_process_lld);
	// ft_commh_add(&(cw->commh), 14, 50, ft_comm_process_lldi);
	// ft_commh_add(&(cw->commh), 15, 1000, ft_comm_process_lfork);
	// ft_commh_add(&(cw->commh), 16, 2, ft_comm_process_aff);
	// ft_commh_add(&(cw->commh_default), 0, 0, ft_comm_process_unknown);
	ft_show_players(cw);
	play = 1;
	cw->cycle = 0;
	while (play)
	{
		ft_tick(cw);
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
	//ft_cw_free(&cw);
	ft_putstr("Status: ");
	ft_putnbr(err);
	ft_putchar('\n');
	ft_info(cw);
	return (0);
}