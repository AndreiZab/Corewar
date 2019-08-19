/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:59:34 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/18 15:52:17 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_instruction	*insts_find(t_corewar *cw, unsigned char byte)
{
	int		i;

	i = -1;
	while (++i < COREWAR_INSTRUCTIONS_COUNT)
		if (cw->instructions[i].byte == byte)
			return (cw->instructions + i);
	return (NULL);
}
