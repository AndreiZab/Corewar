#include "corewar.h"

int		load_option(t_corewar *cw, char *str)
{
	int		i;

	if (ft_strcmp(str, "-dinfo") == 0)
	{
		cw->options |= COREWAR_OPT_DUMP_INFO;
		return (1);
	}
	i = 0;
	while (str[++i])
	{
		if (str[i] == 'c')
			cw->options |= COREWAR_OPT_COLORS;
		else if (str[i] == 'v')
			cw->options |= COREWAR_OPT_VISUALIZER;
		else if (str[i] == 'a')
			cw->options |= COREWAR_OPT_AFF;
		else
			return (0);
	}
	if (i == 1)
		return (0);
	return (1);
}

int		get_options(t_corewar *cw, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && ft_strcmp(argv[i], "-n") != 0 &&
			ft_strcmp(argv[i], "-log") != 0 &&
			ft_strcmp(argv[i], "-dump") != 0)
			if (load_option(cw, argv[i]) == 0)
			{
				ft_putstr(COREWAR_USAGE);
				return (0);
			}
	}
	return (1);
}

int		process_arguments(t_corewar *cw, int argc, char **argv)
{
	int		status;
	int		i;

	if (get_options(cw, argc, argv) == 0)
		return (COREWAR_STATUS_FATAL);
	i = 0;
	status = COREWAR_STATUS_OK;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (ft_strcmp(argv[i], "-n") == 0)
				status = process_flag_n(cw, argc, argv, &i);
			else if (ft_strcmp(argv[i], "-dump") == 0)
				status = process_flag_dump(cw, argc, argv, &i);
			else if (ft_strcmp(argv[i], "-log") == 0)
				status = process_flag_log(cw, argc, argv, &i);
		}
		else
			status = process_file(cw, argv[i]);
		if (status != COREWAR_STATUS_OK)
			return (COREWAR_STATUS_FATAL);
	}
	return (COREWAR_STATUS_OK);
}