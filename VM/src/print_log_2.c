/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:28:33 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/18 15:52:18 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_reg(t_corewar *cw, t_carriage *carr, int *i, int j)
{
	unsigned char	reg_n;

	map_get(cw, 1, *i, &reg_n);
	if (cw->log & COREWAR_OPT_LOG_ORIGINAL)
	{
		if (carr->instruction->argt[j] & DISASM_ORIG_REG)
		{
			ft_putchar('r');
			ft_putnbr(reg_n);
		}
		else if (carr->instruction->argt[j] & DISASM_ORIG_VALUE_IN)
			ft_putnbr(carr->rg[reg_n - 1]);
		else
			ft_putnbr(reg_n);
	}
	*i += 1;
}
