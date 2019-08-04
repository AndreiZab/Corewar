#include "disasm.h"

static void	print_dir(t_exe *exe, t_instruction *inst, int *i, char colored)
{
	unsigned char	num[4];

	(void)colored;
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

static void	print_ind(t_exe *exe, int *i, char colored)
{
	unsigned char	num[4];

	(void)colored;
	ft_bzero(num, 4);
	ft_memcpy(num + 2, exe->data + *i, 2);
	revert_bytes(num + 2, 2);
	ft_putnbr(*((short*)(num + 2)));
	*i += 2;
}

void		print_args(t_exe *exe, t_instruction *inst, int i, char colored)
{
	int				j;

	j = -1;
	ft_putchar('\t');
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_INSTRUCTION);
	ft_putstr(inst->name);
	if (colored)
		ft_setcolor(cc_current, cc_default);
	while (++j < inst->argc)
	{
		ft_putstr((j != 0) ? ", " : " ");
		if (inst->types[j] == REG_CODE)
		{
			ft_putchar('r');
			ft_putnbr(exe->data[i++]);
		}
		else if(inst->types[j] == DIR_CODE)
			print_dir(exe, inst, &i, colored);
		else
			print_ind(exe, &i, colored);
	}
	ft_putchar('\n');
}
