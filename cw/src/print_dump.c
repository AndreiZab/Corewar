/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:01:35 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 13:01:53 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			print_address(t_corewar *cw, int address)
{
	char	*addr;

	if ((addr = casting_uc_hex(address, 4)) == NULL)
		return (COREWAR_STATUS_FATAL);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_white, cc_black);
	ft_putstr("0x");
	ft_putstr(addr);
	ft_putstr(" :");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_default, cc_default);
	free(addr);
	return (COREWAR_STATUS_OK);
}

void		print_map_byte(t_corewar *cw, int pos)
{
	static char			*alpha = "0123456789abcdef";
	unsigned char		id;

	id = cw->players_map[pos];
	ft_putchar(' ');
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, (id > 0 && id <= cw->players_count)
			? (t_ccolor)id : cc_default);
	ft_putchar(alpha[cw->map[pos] / 16]);
	ft_putchar(alpha[cw->map[pos] % 16]);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
}
