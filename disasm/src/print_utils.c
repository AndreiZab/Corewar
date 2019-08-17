/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 11:14:09 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/14 11:14:13 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void	print_col_str(char *str, char options, t_ccolor col)
{
	if (options & DISASM_OPT_COLORS)
		ft_setcolor(cc_current, col);
	ft_putstr(str);
	if (options & DISASM_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
}
