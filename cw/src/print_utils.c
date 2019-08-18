/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:51:20 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:51:22 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_col_str(t_corewar *cw, char *str, t_ccolor col)
{
	if (cw->options & COREWAR_OPT_COLORS)
	{
		ft_setcolor(cc_current, col);
		ft_putstr(str);
		ft_setcolor(cc_current, cc_default);
	}
	else
		ft_putstr(str);
}

void	print_col_nbr(t_corewar *cw, int nbr, t_ccolor col)
{
	if (cw->options & COREWAR_OPT_COLORS)
	{
		ft_setcolor(cc_current, col);
		ft_putnbr(nbr);
		ft_setcolor(cc_current, cc_default);
	}
	else
		ft_putnbr(nbr);
}

void	print_utils_error(t_corewar *cw, char clear_color)
{
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, COREWAR_COLOR_ERROR);
	ft_putstr("Error: ");
	if (clear_color && cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
}

void	print_utils_file(t_corewar *cw, char clear_color)
{
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, COREWAR_COLOR_FILENAME);
	ft_putstr("File '");
	ft_putstr(cw->current_filename);
	ft_putstr("': ");
	if (clear_color && cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
}
