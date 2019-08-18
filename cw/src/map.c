/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:41:53 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:41:54 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		map_normilize(int pos)
{
	pos %= MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	return (pos);
}

void	map_get(t_corewar *cw, int size, int pos, void *output)
{
	int				i;
	unsigned char	*coutput;

	coutput = (unsigned char*)output;
	i = -1;
	while (++i < size)
		coutput[i] = cw->map[map_normilize(pos + size - i - 1)];
}

void	map_set(t_corewar *cw, int size, int pos, void *input)
{
	int				i;
	unsigned char	*cinput;

	cinput = (unsigned char*)input;
	i = -1;
	while (++i < size)
		cw->map[map_normilize(pos + size - i - 1)] = cinput[i];
}

void	map_set_color(t_corewar *cw, int pos, int size, unsigned char owner_id)
{
	int		i;

	i = -1;
	while (++i < size)
		cw->players_map[map_normilize(pos + i)] = owner_id;
}
