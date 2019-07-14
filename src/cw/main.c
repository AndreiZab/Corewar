#include "ft_cw.h"

int		ft_prepare_field(t_corewar *cw)
{
	int mem_part;
	int i;

	ft_bzero(cw->map, MEM_SIZE);
	mem_part = MEM_SIZE / cw->players_count;
	i = -1;
	while (++i < cw->players_count)
	{
		ft_memcpy(cw->map[i * mem_part], cw->players[i].exe,
			cw->players[i].exe_size);
	}
	return (FT_OK);
}

int		main(int argc, char **argv)
{
	t_corewar	cw;
	int			err;

	err = FT_OK;
	err = ft_process_args(&cw, argc, argv);
	if (err == FT_OK)
		err = ft_prepare_field(&cw);
	//if (err == FT_OK)
	//	err = ft_play(&cw);
	//ft_output(&cw);
	//ft_cw_free(&cw);
	return (0);
}