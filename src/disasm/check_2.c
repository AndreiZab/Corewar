#include "disasm.h"

static void	get_types(char types[3], char from)
{
	types[0] = (from & 0b11000000) >> 6;
	types[1] = (from & 0b00110000) >> 4;
	types[2] = (from & 0b00001100) >> 2;
}

static int	get_size(t_instruction *inst, char type)
{
	if (type == REG_CODE)
		return (1);
	if (type == IND_CODE)
		return (2);
	if (type == DIR_CODE)
		return (inst->dir_size);
	return (0);
}

static int	check_arg(char permission, char current)
{
	if ((permission & DISASM_REG && current == REG_CODE) ||
		(permission & DISASM_DIR && current == DIR_CODE) ||
		(permission & DISASM_IND && current == IND_CODE))
		return (1);
	return (0);
}

static int	check_type(t_exe *exe, t_instruction *inst, int i, char colored)
{
	int		j;

	if (inst->type_byte)
	{
		if (++i < exe->size)
		{
			get_types(inst->types, exe->data[i]);
			j = -1;
			while (++j < inst->argc)
				if (!check_arg(inst->argt[j], inst->types[j]))
					return (print_error_inst(inst->name, "Wrong argument type",
						colored) - 1);
		}
		else
			return (print_error_inst(inst->name,
				"Champion's code was ended before type byte", colored) - 1);		
	}
	else
	{
		inst->types[0] = REG_CODE;
		if (inst->argt[0] != DISASM_REG)
			inst->types[0] = (inst->argt[0] == DISASM_DIR) ?
				DIR_CODE : IND_CODE;
	}
	return (i);
}

int			check_instruction(t_exe *exe, t_instruction *inst, int i,
				char colored)
{
	int				arg1_size;
	int				arg2_size;
	int				arg3_size;
	
	i = check_type(exe, inst, i, colored);
	if (i < 0)
		return (-1);
	arg1_size = get_size(inst, inst->types[0]);
	arg2_size = (inst->argc >= 2) ? get_size(inst, inst->types[1]) : 0;
	arg3_size = (inst->argc >= 3) ? get_size(inst, inst->types[2]) : 0;
	++i;
	if (i + arg1_size + arg2_size + arg3_size > exe->size)
		return (print_error_inst(inst->name, "No enough space", colored) - 1);
	print_args(exe, inst, i, colored);
	return (i + arg1_size + arg2_size + arg3_size);
}
