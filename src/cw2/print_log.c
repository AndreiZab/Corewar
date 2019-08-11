#include "corewar.h"

static void		print_dir(t_corewar *cw, t_instruction *inst, int *i)
{
	unsigned char	num[4];

	ft_bzero(num, 4);
	map_get(cw, inst->dir_size, *i, num + ((inst->dir_size == 2) ? 2 : 0));
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

static void		print_executed(t_corewar *cw, t_instruction *inst, int i)
{
	int				j;
	unsigned char	reg_n;

	j = -1;
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_blue);
	ft_putstr(inst->name);
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
	while (++j < inst->argc)
	{
		ft_putstr((j != 0) ? ", " : " ");
		if (cw->temp_types[j] == REG_CODE)
		{
			ft_putchar('r');
			map_get(cw, 1, i++, &reg_n);
			ft_putnbr(reg_n);
		}
		else if(cw->temp_types[j] == DIR_CODE)
			print_dir(cw, inst, &i);
		else
			print_ind(cw, &i);
	}
}

void			print_log(t_corewar *cw, t_carriage *carr)
{
	int		pos;

	ft_putstr("P\t");
	ft_putnbr(carr->id);
	ft_putstr("|  ");
	pos = carr->pc_comm + 1 + ((carr->instruction->type_byte) ? 1 : 0);
	print_executed(cw, carr->instruction, pos);
}