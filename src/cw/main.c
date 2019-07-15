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
	ft_argh_add(&cw->argh, "-n", ft_process_flag_n); // Обработка флагов
	ft_argh_add(&cw->argh, "-v", ft_process_flag_v);
	ft_argh_add(&cw->argh, "-dump", ft_process_flag_dump);
	ft_argh_add(&cw->argh_default, NULL, ft_process_file); // Обработка названий файлов
	arg_i = 0;
	err = FT_OK;
	while (err == FT_OK && ++arg_i < argc)
		err = ft_argh_do(cw, argc, argv, &arg_i);
	ft_argh_free(&cw->argh);
	ft_argh_free(&cw->argh_default);
	if (err == FT_OK)
		ft_player_delete(&(cw->players));
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
	i = -1;
	pl = cw->players;
	while (++i < cw->players_count)
	{
		ft_memcpy(cw->map + i * mem_part, pl->exe, pl->exe_size);
		pl = pl->next;
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
		ft_putstr("\n\n");
		player = player->next;
	}
}

static int		ft_play(t_corewar *cw)
{
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