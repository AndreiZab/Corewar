/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:57:35 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/17 11:57:42 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		load_checks(t_corewar *cw)
{
	cw->checks[0] = check_magic_header;
	cw->checks[1] = check_name;
	cw->checks[2] = check_null;
	cw->checks[3] = check_code_size;
	cw->checks[4] = check_comment;
	cw->checks[5] = check_null;
	cw->checks[6] = check_exe;
	cw->checks[7] = check_eof;
}

t_corewar		*corewar_init(int *status)
{
	t_corewar	*cw;

	if ((cw = (t_corewar*)ft_memalloc(sizeof(t_corewar))) == NULL)
	{
		*status = COREWAR_STATUS_FATAL;
		return (NULL);
	}
	load_checks(cw);
	load_instructions(cw);
	cw->dump = -1;
	cw->cycle_to_die = CYCLE_TO_DIE;
	cw->die_step = CYCLE_TO_DIE;
	return (cw);
}

void			players_free(t_corewar *cw)
{
	t_player	*pl;
	int			i;

	i = -1;
	while (++i < cw->players_count)
	{
		pl = cw->players + i;
		if (pl->name)
			free(pl->name);
		if (pl->comment)
			free(pl->comment);
		if (pl->code)
			free(pl->code);
		pl->name = NULL;
		pl->comment = NULL;
		pl->code = NULL;
	}
}

void			carriages_free(t_corewar *cw)
{
	t_carriage	*current;
	t_carriage	*next;

	current = cw->carrs;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	cw->carrs = NULL;
}

void			corewar_free(t_corewar **corewar)
{
	t_corewar	*cw;

	if (corewar && *corewar)
	{
		cw = *corewar;
		players_free(cw);
		carriages_free(cw);
		free(cw);
		*corewar = NULL;
	}
}
