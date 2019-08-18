/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:02:21 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 13:02:23 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_error(char *str, t_corewar *cw)
{
	print_utils_error(cw, 1);
	ft_putstr(str);
	ft_putchar('\n');
	return (COREWAR_STATUS_FATAL);
}

int		print_error_file(char *str, t_corewar *cw)
{
	print_utils_error(cw, 0);
	print_utils_file(cw, 1);
	ft_putstr(str);
	ft_putchar('\n');
	return (COREWAR_STATUS_FATAL);
}

int		print_error_file_unknown_inst(unsigned char byte, t_corewar *cw)
{
	char		*str;
	static char	alpha[] = "0123456789abcdef";

	if ((str = ft_strdup("Unknown instruction **")) == NULL)
		return (print_error("DISASM Memory Error", cw));
	str[20] = alpha[byte / 16];
	str[21] = alpha[byte % 16];
	print_error_file(str, cw);
	free(str);
	return (COREWAR_STATUS_FATAL);
}

int		print_error_file_inst(char *inst, char *str, t_corewar *cw)
{
	print_utils_error(cw, 0);
	print_utils_file(cw, 1);
	ft_putstr("Instruction '");
	ft_putstr(inst);
	ft_putstr("': ");
	ft_putstr(str);
	ft_putchar('\n');
	return (COREWAR_STATUS_FATAL);
}

void	print_now_cycle(t_corewar *cw)
{
	ft_putstr("It is now cycle ");
	print_col_nbr(cw, cw->cycle, COREWAR_COLOR_CYCLE);
	ft_putchar('\n');
}
