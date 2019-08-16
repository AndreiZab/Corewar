/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:41:40 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:41:41 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_dir(t_corewar *cw, t_instruction *inst, int *i)
{
	unsigned char	num[4];

	ft_bzero(num, 4);
	map_get(cw, inst->dir_size, *i, num + ((inst->dir_size == 2) ? 2 : 0));
	if (!(cw->log & COREWAR_OPT_LOG_ORIGINAL))
		ft_putchar('%');
	if (inst->dir_size == 2)
		ft_putnbr(*((short*)(num + 2)));
	else
		ft_putnbr(*((int*)num));
	*i += inst->dir_size;
}

static void		print_ind(t_corewar *cw, int *i)
{
	unsigned char	num[2];

	ft_bzero(num, 2);
	map_get(cw, 2, *i, num);
	ft_putnbr(*((short*)(num)));
	*i += 2;
}

static void		print_executed(t_corewar *cw, t_carriage *carr, int i)
{
	int				j;

	j = -1;
	print_col_str(cw, carr->instruction->name, COREWAR_COLOR_INSTRUCTION);
	while (++j < carr->instruction->argc)
	{
		ft_putstr((j != 0 && !(cw->log & COREWAR_OPT_LOG_ORIGINAL))
			? ", " : " ");
		if (cw->temp_types[j] == REG_CODE)
			print_reg(cw, carr, &i, j);
		else if (cw->temp_types[j] == DIR_CODE)
			print_dir(cw, carr->instruction, &i);
		else
			print_ind(cw, &i);
	}
}

void			print_nbr_width(int nbr, int width)
{
	char	*str;
	int		i;

	if ((str = ft_itoa(nbr)) != NULL)
	{
		i = width - ft_strlen(str);
		while (i-- > 0)
			ft_putchar(' ');
		ft_putstr(str);
		free(str);
	}
}

void			print_log(t_corewar *cw, t_carriage *carr)
{
	int		pos;

	ft_putstr("P");
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, COREWAR_COLOR_CARRIAGE);
	print_nbr_width(carr->id, 5);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
	ft_putstr(" | ");
	pos = carr->pc_comm + 1 + ((carr->instruction->type_byte) ? 1 : 0);
	print_executed(cw, carr, pos);
}
