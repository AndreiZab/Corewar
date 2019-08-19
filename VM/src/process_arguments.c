/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:40:42 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/18 15:52:17 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_usage(void)
{
	ft_putstr("usage: ./corewar [-cva] [-dump nbr_cycles] [-dinfo] ");
	ft_putstr("[[-n champ_number] champ.cor]\n");
	ft_putstr("Flags:\n");
	ft_putstr("\t-c - colored mode\n");
	ft_putstr("\t-v - visualization mode\n");
	ft_putstr("\t-a - enable aff output\n");
	ft_putstr("Dump memory:\n");
	ft_putstr("\t-dump nbr_cycle - output dump memory\n");
	ft_putstr("\t-dinfo - output additional information on -dump\n");
	ft_putstr("Champions:\n");
	ft_putstr("\t-n champ_number - set number of the champion\n");
	ft_putstr("\tchamp.cor - binary file with champions code\n");
}

int		get_options(t_corewar *cw, int argc, char **argv)
{
	int		i;

	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && ft_strcmp(argv[i], "-n") != 0 &&
			ft_strcmp(argv[i], "-log") != 0 &&
			ft_strcmp(argv[i], "-dump") != 0)
			if (load_option(cw, argv[i]) == 0)
			{
				print_usage();
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
