#include "disasm.h"

static void		argt_set(t_instruction *inst, char arg1, char arg2, char arg3)
{
	int		i;

	inst->argt[0] = arg1;
	inst->argt[1] = arg2;
	inst->argt[2] = arg3;
	i = -1;
	while (++i < 3)
	{
		if (inst->argt[i] == 0)
			break;
	}
	inst->argc = i;
}

static int		load_instructions_2(t_exe *exe)
{
	int		loaded;

	loaded = 0;
	loaded += inst_add(&(exe->insts), "lfork", 15, 0);
	argt_set(exe->insts, DISASM_DIR, 0, 0);
	exe->insts->dir_size = 2;
	loaded += inst_add(&(exe->insts), "aff", 16, 1);
	argt_set(exe->insts, DISASM_REG, 0, 0);
	return (1);
}

static int		load_instructions_1(t_exe *exe)
{
	int		loaded;

	loaded = 0;
	loaded += inst_add(&(exe->insts), "zjmp", 9, 0);
	argt_set(exe->insts, DISASM_DIR, 0, 0);
	exe->insts->dir_size = 2;
	loaded += inst_add(&(exe->insts), "ldi", 10, 1);
	argt_set(exe->insts, DISASM_REG | DISASM_DIR | DISASM_IND,
		DISASM_REG | DISASM_DIR, DISASM_REG);
	exe->insts->dir_size = 2;
	loaded += inst_add(&(exe->insts), "sti", 11, 1);
	argt_set(exe->insts, DISASM_REG,
		DISASM_REG | DISASM_DIR | DISASM_IND, DISASM_REG | DISASM_DIR);
	exe->insts->dir_size = 2;
	loaded += inst_add(&(exe->insts), "fork", 12, 0);
	argt_set(exe->insts, DISASM_DIR, 0, 0);
	exe->insts->dir_size = 2;
	loaded += inst_add(&(exe->insts), "lld", 13, 1);
	argt_set(exe->insts, DISASM_DIR | DISASM_IND, DISASM_REG, 0);
	loaded += inst_add(&(exe->insts), "lldi", 14, 1);
	argt_set(exe->insts, DISASM_REG | DISASM_DIR | DISASM_IND,
		DISASM_REG | DISASM_DIR, DISASM_REG);
	exe->insts->dir_size = 2;
	return (loaded == 6 ? load_instructions_2(exe) : 0);
}

int				load_instructions(t_exe *exe)
{
	int		loaded;

	loaded = 0;
	loaded += inst_add(&(exe->insts), "live", 1, 0);
	argt_set(exe->insts, DISASM_DIR, 0, 0);
	loaded += inst_add(&(exe->insts), "ld", 2, 1);
	argt_set(exe->insts, DISASM_DIR | DISASM_IND, DISASM_REG, 0);
	loaded += inst_add(&(exe->insts), "st", 3, 1);
	argt_set(exe->insts, DISASM_REG, DISASM_REG | DISASM_IND, 0);
	loaded += inst_add(&(exe->insts), "add", 4, 1);
	argt_set(exe->insts, DISASM_REG, DISASM_REG, DISASM_REG);
	loaded += inst_add(&(exe->insts), "sub", 5, 1);
	argt_set(exe->insts, DISASM_REG, DISASM_REG, DISASM_REG);
	loaded += inst_add(&(exe->insts), "and", 6, 1);
	argt_set(exe->insts, DISASM_REG | DISASM_DIR | DISASM_IND,
		DISASM_REG | DISASM_DIR | DISASM_IND, DISASM_REG);
	loaded += inst_add(&(exe->insts), "or", 7, 1);
	argt_set(exe->insts, DISASM_REG | DISASM_DIR | DISASM_IND,
		DISASM_REG | DISASM_DIR | DISASM_IND, DISASM_REG);
	loaded += inst_add(&(exe->insts), "xor", 8, 1);
	argt_set(exe->insts, DISASM_REG | DISASM_DIR | DISASM_IND,
		DISASM_REG | DISASM_DIR | DISASM_IND, DISASM_REG);
	return (loaded == 8 ? load_instructions_1(exe) : 0);
}
