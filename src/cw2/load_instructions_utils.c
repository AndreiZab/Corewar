#include "corewar.h"

void		set_instruction_base(t_instruction *inst, unsigned char byte,
				char *name, char type_byte)
{
	inst->byte = byte;
	inst->name = name;
	inst->type_byte = type_byte;
}

void		set_instruction_args(t_instruction *inst, char arg1, char arg2,
				char arg3)
{
	inst->argt[0] = arg1;
	inst->argt[1] = arg2;
	inst->argt[2] = arg3;
	if (arg3 != 0)
		inst->argc = 3;
	else if (arg2 != 0)
		inst->argc = 2;
	else
		inst->argc = 1;
}

void		set_instruction_other(t_instruction *inst, int dir_size,
				int sleep, int (*f)(t_corewar*, t_carriage*))
{
	inst->dir_size = dir_size;
	inst->sleep = sleep;
	inst->f = f;
}