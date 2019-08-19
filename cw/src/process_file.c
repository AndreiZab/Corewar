/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:41:18 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:41:19 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_next_id(t_corewar *cw)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (!cw->players[i].set)
			return (i + 1);
	return (1);
}

int		process_file(t_corewar *cw, char *filename)
{
	t_player	*pl;
	int			fd;
	int			i;

	if (cw->players_count == MAX_PLAYERS)
		return (print_error("Too many players", cw));
	if (cw->next_id == 0)
		cw->next_id = get_next_id(cw);
	pl = cw->players + cw->next_id - 1;
	cw->current_filename = filename;
	if (!end_with(filename, ".cor"))
		return (print_error_file(".cor file expected", cw));
	if ((fd = open(filename, O_RDONLY)) <= 0)
		return (print_error_file("Can't open this file", cw));
	i = -1;
	while (++i < COREWAR_CHECKS_COUNT)
		if (cw->checks[i](fd, cw, pl) != COREWAR_STATUS_OK)
			return (COREWAR_STATUS_FATAL);
	pl->set = 1;
	cw->next_id = 0;
	++(cw->players_count);
	return (COREWAR_STATUS_OK);
}
