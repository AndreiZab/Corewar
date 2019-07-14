#include "ft_cw.h"

/*
** RU
** Обработчики аргументов
*/

int ft_process_flag_dump(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	ft_putstr("Flag -dump\n");
	return (FT_OK);
}

int	ft_process_flag_n(t_corewar *cw, int argc, char **argv, int *arg_i)
{
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
	ft_putstr("Flag -n: has value = ");
	ft_putstr(argv[*arg_i]);
	ft_putchar('\n');
	return (FT_OK);
}

int ft_process_file(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	ft_putstr("File: ");
	ft_putstr(argv[*arg_i]);
	ft_putchar('\n');
	return (FT_OK);
}