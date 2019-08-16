/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:28:33 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 13:28:35 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_reg(t_corewar *cw, t_carriage *carr, int *i, int j)
{
	unsigned char	reg_n;

	map_get(cw, 1, (*i)++, &reg_n);
	if (carr->instruction->argt[j] & DISASM_LINK ||
		cw->options & COREWAR_OPT_LOG_ORIGINAL)
	{
		ft_putchar('r');
		ft_putnbr(reg_n);
	}
	else
	{
		if (regnumber_contains(reg_n))
			ft_putnbr(carr->rg[reg_n - 1]);
		else
			ft_putstr("rNAN");
	}
}
