/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:57:09 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/18 15:52:18 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		check_executable(t_corewar *cw, t_player *pl)
{
	t_instruction	*inst;
	int				i;

	i = 0;
	while (i < pl->size)
	{
		inst = insts_find(cw, pl->code[i]);
		if (inst == NULL)
			return (print_error_file_unknown_inst(pl->code[i], cw));
		i = check_instruction(cw, pl, inst, i);
		if (i == COREWAR_STATUS_FATAL)
			return (COREWAR_STATUS_FATAL);
	}
	return (COREWAR_STATUS_OK);
}

int				check_exe(int fd, t_corewar *cw, t_player *pl)
{
	unsigned char	buff[pl->size + 1];

	if (accurate_read(fd, (char*)buff, pl->size) <= 0)
		return (print_error_file("Can't read champion's code", cw));
	if ((pl->code = ft_memalloc(sizeof(char) * pl->size)) == NULL)
		return (print_error("Corewar Memory Error", cw));
	ft_memcpy(pl->code, buff, pl->size);
	return (check_executable(cw, pl));
}

int				check_eof(int fd, t_corewar *cw, t_player *pl)
{
	char	buff[1];

	(void)pl;
	if (accurate_read(fd, buff, 1) > 0)
		return (print_error_file("Expected EOF after champion's code", cw));
	return (COREWAR_STATUS_OK);
}
