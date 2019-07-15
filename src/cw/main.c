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
	return (err);
}

int				ft_prepare_field(t_corewar *cw)
{
	// int mem_part;
	// int i;

	// ft_bzero(cw->map, MEM_SIZE);
	// mem_part = MEM_SIZE / cw->players_count;
	// i = -1;
	// while (++i < cw->players_count)
	// {
	// 	ft_memcpy(cw->map[i * mem_part], cw->players[i].exe,
	// 		cw->players[i].exe_size);
	// }
	return (FT_OK);
}

int				main(int argc, char **argv)
{
	t_corewar	*cw;
	int			err;

	cw = ft_cw_alloc(&err);
	err == FT_OK ? err = ft_process_args(cw, argc, argv) : 0;
	ft_putnbr(err);
	//if (err == FT_OK)
	//	err = ft_prepare_field(&cw);
	//if (err == FT_OK)
	//	err = ft_play(&cw);
	//ft_output(&cw);
	//ft_cw_free(&cw);
	return (0);
}