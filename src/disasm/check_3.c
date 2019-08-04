#include "disasm.h"

static t_exe	*exe_create(unsigned char *buff, int code_size)
{
	t_exe	*exe;

	if ((exe = (t_exe*)ft_memalloc(sizeof(t_exe))) == NULL)
		return (NULL);
	if (load_instructions(exe) == 0)
	{
		free(exe);
		return (NULL);
	}
	exe->data = buff;
	exe->size = code_size;
	return (exe);
}

static void		exe_free(t_exe *exe)
{
	t_instruction	*inst;
	t_instruction	*inst_next;

	inst = exe->insts;
	while (inst)
	{
		inst_next = inst->next;
		free(inst->name);
		free(inst);
		inst = inst_next;
	}
	free(exe);
}

static int		check_executable(t_exe *exe, char colored)
{
	t_instruction	*inst;
	int				i;

	i = 0;
	while (i < exe->size)
	{
		inst = inst_find(exe->insts, exe->data[i]);
		if (inst == NULL)
			return (print_error_unknown_inst(exe->data[i], colored));
		i = check_instruction(exe, inst, i, colored);
		if (i < 0)
			return (0);
	}
	exe_free(exe);
	return (1);
}

int		check_exe(int fd, int code_size, char colored)
{
	unsigned char	buff[code_size + 1];
	t_exe			*exe;

	if (accurate_read(fd, (char*)buff, code_size) <= 0)
		return (print_error("Can't read champion's code", colored));
	if ((exe = exe_create(buff, code_size)) == NULL)
		return (print_error("DISASM Memory Error", colored));
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_NAME);
	ft_putstr("Instructions:\n");
	if (colored)
		ft_setcolor(cc_current, cc_default);
	return (check_executable(exe, colored));
}

int		check_eof(int fd, char colored)
{
	char	buff[1];

	if (accurate_read(fd, buff, 1) > 0)
		return (print_error("Expected EOF after champion's code", colored));
	return (1);
}
