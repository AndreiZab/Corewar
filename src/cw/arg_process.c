#include "ft_cw.h"

/*
** RU
** Обработчики аргументов
*/

int ft_process_flag_dump(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	int		dump_val;

	++(*arg_i);
	if (*arg_i == argc)
	{
		ft_putstr("Flag -dump: has no value\n");
		return (FT_ARG);
	}
	if (!ft_isint(argv[*arg_i]))
	{
		ft_putstr("Flag -dump: must be int\n");
		return (FT_ARG);
	}
	//dump_val сделать uint или даже ulonglongint
	dump_val = ft_atoi(argv[*arg_i]);
	if (dump_val <= 0)
	{
		ft_putstr("Flag -dump: value must be positive\n");
		return (FT_ARG);
	}
	cw->dump_mode = 1;
	cw->dump_cycle = dump_val;
	ft_putstr("Flag -dump: has value = ");
	ft_putstr(argv[*arg_i]);
	ft_putchar('\n');
	return (FT_OK);
}

int	ft_process_flag_v(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	cw->v = 1;
	return (FT_OK);
}

/*
** Проверить, задан ли уже этот id игрока
*/

static int ft_contains_ids(t_corewar *cw, int id)
{
	t_player	*player;

	player = cw->players->next;
	while (player)
	{
		if (id == player->id)
			return (1);
		player = player->next;
	}
	return (0);
}

int	ft_process_flag_n(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	int		n_val;

	++(*arg_i);
	if (*arg_i == argc)
	{
		ft_putstr("Flag -n: has no value\n");
		return (FT_ARG);
	}
	if (!ft_isint(argv[*arg_i]))
	{
		ft_putstr("Flag -n: must be int\n");
		return (FT_ARG);
	}
	//n_val сделать uint
	n_val = ft_atoi(argv[*arg_i]);
	if (n_val <= 0 || n_val > MAX_PLAYERS)
	{
		ft_putstr("Flag -n: value must be in range [1;");
		ft_putnbr(MAX_PLAYERS);
		ft_putstr("]\n");
		return (FT_ARG);
	}
	if (ft_contains_ids(cw, n_val))
	{
		ft_putstr("Flag -n: this player number already set\n");
		return (FT_ARG);
	}
	ft_putstr("Flag -n: has value = ");
	ft_putstr(argv[*arg_i]);
	ft_putchar('\n');
	cw->players->id = n_val;
	return (FT_OK);
}

int ft_process_file(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	//необходима проверка на расширение файла .cor
	ft_putstr("File: ");
	ft_putstr(argv[*arg_i]);
	ft_putchar('\n');
	return (FT_OK);
}