/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:49:46 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/14 10:49:50 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int			print_usage(void)
{
	ft_putstr("usage: ./disasm [-cf] file1.cor [file2.cor ...]\n");
	ft_putstr("\t-c - colored mode\n");
	ft_putstr("\t-f - file-format mode\n");
	return (0);
}

static void	print_dir(t_exe *exe, t_instruction *inst, int *i, char options)
{
	unsigned char	num[4];

	(void)options;
	ft_bzero(num, 4);
	ft_memcpy(num + ((inst->dir_size == 4) ? 0 : 2), exe->data + *i,
		inst->dir_size);
	revert_bytes(num + ((inst->dir_size == 4) ? 0 : 2), inst->dir_size);
	ft_putchar('%');
	if (inst->dir_size == 2)
		ft_putnbr(*((short*)(num + 2)));
	else
		ft_putnbr(*((int*)num));
	*i += inst->dir_size;
}

static void	print_ind(t_exe *exe, int *i, char options)
{
	unsigned char	num[4];

	(void)options;
	ft_bzero(num, 4);
	ft_memcpy(num + 2, exe->data + *i, 2);
	revert_bytes(num + 2, 2);
	ft_putnbr(*((short*)(num + 2)));
	*i += 2;
}

void		print_args(t_exe *exe, t_instruction *inst, int i, char options)
{
	int				j;

	j = -1;
	ft_putchar('\t');
	print_col_str(inst->name, options, DISASM_COL_INSTRUCTION);
	while (++j < inst->argc)
	{
		ft_putstr((j != 0) ? ", " : " ");
		if (inst->types[j] == REG_CODE)
		{
			ft_putchar('r');
			ft_putnbr(exe->data[i++]);
		}
		else if (inst->types[j] == DIR_CODE)
			print_dir(exe, inst, &i, options);
		else
			print_ind(exe, &i, options);
	}
	ft_putchar('\n');
}
