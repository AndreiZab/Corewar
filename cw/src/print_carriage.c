/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_carriage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:51:32 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:51:35 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_bytes(t_corewar *cw, int pos, int count)
{
	static char		*alpha = "0123456789abcdef";
	unsigned char	byte;

	while (count--)
	{
		map_get(cw, 1, pos, &byte);
		ft_putchar(' ');
		ft_putchar(alpha[byte / 16]);
		ft_putchar(alpha[byte % 16]);
		++pos;
	}
}

void	print_move_address(t_corewar *cw, int address)
{
	char *str;

	str = casting_uc_hex(address, 4);
	print_col_str(cw, "0x", COREWAR_COLOR_ADDRESS);
	print_col_str(cw, str, COREWAR_COLOR_ADDRESS);
	free(str);
}

void	print_pc_movements(t_corewar *cw, t_carriage *carr)
{
	int		bytes;
	int		i;

	if (carr->instruction == NULL ||
		(carr->instruction->byte == 9 && carr->carry))
		return ;
	ft_putstr("ADV ");
	ft_putnbr(map_normilize(carr->pc - carr->pc_comm));
	ft_putstr(" (");
	print_move_address(cw, carr->pc_comm);
	ft_putstr(" -> ");
	print_move_address(cw, carr->pc_comm +
		map_normilize(carr->pc - carr->pc_comm));
	ft_putstr(")");
	bytes = (carr->instruction->type_byte) ? 2 : 1;
	i = -1;
	while (++i < carr->instruction->argc)
		bytes += get_size(carr->instruction, cw->temp_types[i]);
	print_bytes(cw, carr->pc_comm, bytes);
	ft_putchar('\n');
}
