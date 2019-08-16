/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:40:10 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 15:59:56 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		print_error_range(t_corewar *cw)
{
	print_error("", cw);
	ft_putstr("Flag -n: value must be in range [1;");
	ft_putnbr(MAX_PLAYERS);
	ft_putstr("]\n");
	return (COREWAR_STATUS_FATAL);
}

int				process_flag_log(t_corewar *cw, int argc, char **argv, int *i)
{
	char	i_val;

	++(*i);
	if (*i == argc)
		return (print_error("Flag -log: has no value", cw));
	if (!ft_isint(argv[*i]))
		return (print_error("Flag -log: must be number", cw));
	i_val = (char)ft_atoi(argv[*i]);
	cw->log |= i_val;
	return (COREWAR_STATUS_OK);
}

int				process_flag_n(t_corewar *cw, int argc, char **argv, int *i)
{
	int		n_val;

	++(*i);
	if (*i == argc)
		return (print_error("Flag -n: has no value", cw));
	if (!ft_isint(argv[*i]))
		return (print_error("Flag -n: must be int", cw));
	n_val = ft_atoi(argv[*i]);
	if (n_val <= 0 || n_val > MAX_PLAYERS)
		return (print_error_range(cw));
	if (cw->players[n_val - 1].set)
		return (print_error("Flag -n: this player number already set", cw));
	cw->next_id = n_val;
	return (COREWAR_STATUS_OK);
}

int				process_flag_dump(t_corewar *cw, int argc, char **argv, int *i)
{
	int		dump_val;

	++(*i);
	if (*i == argc)
		return (print_error("Flag -dump: has no value", cw));
	if (!ft_isint(argv[*i]))
		return (print_error("Flag -dump: must be int", cw));
	dump_val = ft_atoi(argv[*i]);
	if (dump_val <= 0)
		return (print_error("Flag -dump: value must be positive number", cw));
	cw->dump = dump_val;
	return (COREWAR_STATUS_OK);
}
