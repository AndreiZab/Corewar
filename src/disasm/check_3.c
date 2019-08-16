/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:54:02 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/14 10:54:04 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int		check_executable(t_exe *exe, char options)
{
	t_instruction	*inst;
	int				i;

	i = 0;
	while (i < exe->size)
	{
		inst = inst_find(exe->insts, exe->data[i]);
		if (inst == NULL)
			return (print_error_unknown_inst(exe->data[i], options));
		i = check_instruction(exe, inst, i, options);
		if (i < 0)
			return (0);
	}
	exe_free(exe);
	return (1);
}

int				check_exe(int fd, char options, void *arg)
{
	unsigned char	buff[*((int*)arg) + 1];
	t_exe			*exe;
	int				code_size;

	code_size = *((int*)arg);
	if (accurate_read(fd, (char*)buff, code_size) <= 0)
		return (print_error("Can't read champion's code", options));
	if ((exe = exe_create(buff, code_size)) == NULL)
		return (print_error("DISASM Memory Error", options));
	if (options & DISASM_OPT_COLORS)
		ft_setcolor(cc_current, DISASM_COL_NAME);
	if (!(options & DISASM_OPT_FILE_FORMAT))
		ft_putstr("Instructions:\n");
	if (options & DISASM_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
	return (check_executable(exe, options));
}

int				check_eof(int fd, char options, void *arg)
{
	char	buff[1];

	(void)arg;
	if (accurate_read(fd, buff, 1) > 0)
		return (print_error("Expected EOF after champion's code", options));
	return (1);
}
