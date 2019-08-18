/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:11:47 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 13:11:49 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		load_instructions_3(t_corewar *cw)
{
	set_instruction_base(cw->instructions + 14, 15, "lfork", 0);
	set_instruction_args(cw->instructions + 14, DISASM_DIR, 0, 0);
	set_instruction_other(cw->instructions + 14, 2, 1000, lfork_function);
	set_instruction_base(cw->instructions + 15, 16, "aff", 1);
	set_instruction_args(cw->instructions + 15, DISASM_REG, 0, 0);
	set_instruction_other(cw->instructions + 15, 4, 2, aff_function);
}

static void		load_instructions_2(t_corewar *cw)
{
	set_instruction_base(cw->instructions + 9, 10, "ldi", 1);
	set_instruction_args(cw->instructions + 9, DISASM_REG | DISASM_DIR |
		DISASM_IND, DISASM_REG | DISASM_DIR | DISASM_ORIG_VALUE_IN,
		DISASM_REG | DISASM_LINK | DISASM_ORIG_REG);
	set_instruction_other(cw->instructions + 9, 2, 25, ldi_function);
	set_instruction_base(cw->instructions + 10, 11, "sti", 1);
	set_instruction_args(cw->instructions + 10, DISASM_REG | DISASM_LINK |
		DISASM_ORIG_REG, DISASM_REG | DISASM_DIR | DISASM_IND |
		DISASM_ORIG_VALUE_IN | DISASM_IDX | COREWAR_IDX,
		DISASM_REG | DISASM_DIR | DISASM_ORIG_VALUE_IN | DISASM_LINK);
	set_instruction_other(cw->instructions + 10, 2, 25, sti_function);
	set_instruction_base(cw->instructions + 11, 12, "fork", 0);
	set_instruction_args(cw->instructions + 11, DISASM_DIR, 0, 0);
	set_instruction_other(cw->instructions + 11, 2, 800, fork_function);
	set_instruction_base(cw->instructions + 12, 13, "lld", 1);
	set_instruction_args(cw->instructions + 12, DISASM_DIR | DISASM_IND,
		DISASM_REG, 0);
	set_instruction_other(cw->instructions + 12, 4, 10, lld_function);
	set_instruction_base(cw->instructions + 13, 14, "lldi", 1);
	set_instruction_args(cw->instructions + 13, DISASM_REG | DISASM_DIR |
		DISASM_IND, DISASM_REG | DISASM_DIR, DISASM_REG);
	set_instruction_other(cw->instructions + 13, 2, 50, lldi_function);
	load_instructions_3(cw);
}

static void		load_instructions_1(t_corewar *cw)
{
	set_instruction_base(cw->instructions + 5, 6, "and", 1);
	set_instruction_args(cw->instructions + 5, DISASM_REG | DISASM_DIR
		| DISASM_IND, DISASM_REG | DISASM_DIR | DISASM_IND,
		DISASM_REG | DISASM_LINK);
	set_instruction_other(cw->instructions + 5, 4, 6, and_function);
	set_instruction_base(cw->instructions + 6, 7, "or", 1);
	set_instruction_args(cw->instructions + 6, DISASM_REG | DISASM_DIR |
		DISASM_IND | DISASM_ORIG_VALUE_IN, DISASM_REG | DISASM_DIR |
		DISASM_IND | DISASM_ORIG_VALUE_IN,
		DISASM_REG | DISASM_LINK | DISASM_ORIG_REG);
	set_instruction_other(cw->instructions + 6, 4, 6, or_function);
	set_instruction_base(cw->instructions + 7, 8, "xor", 1);
	set_instruction_args(cw->instructions + 7, DISASM_REG | DISASM_DIR |
		DISASM_IND | DISASM_ORIG_VALUE_IN, DISASM_REG | DISASM_DIR |
		DISASM_IND | DISASM_ORIG_VALUE_IN,
		DISASM_REG | DISASM_LINK | DISASM_ORIG_REG);
	set_instruction_other(cw->instructions + 7, 4, 6, xor_function);
	set_instruction_base(cw->instructions + 8, 9, "zjmp", 0);
	set_instruction_args(cw->instructions + 8, DISASM_DIR, 0, 0);
	set_instruction_other(cw->instructions + 8, 2, 20, zjmp_function);
	load_instructions_2(cw);
}

void			load_instructions(t_corewar *cw)
{
	set_instruction_base(cw->instructions + 0, 1, "live", 0);
	set_instruction_args(cw->instructions + 0, DISASM_DIR, 0, 0);
	set_instruction_other(cw->instructions + 0, 4, 10, live_function);
	set_instruction_base(cw->instructions + 1, 2, "ld", 1);
	set_instruction_args(cw->instructions + 1, DISASM_DIR | DISASM_IND |
		DISASM_ORIG_VALUE_IN | DISASM_IDX, DISASM_REG | DISASM_LINK |
		DISASM_ORIG_REG, 0);
	set_instruction_other(cw->instructions + 1, 4, 5, ld_function);
	set_instruction_base(cw->instructions + 2, 3, "st", 1);
	set_instruction_args(cw->instructions + 2, DISASM_REG | DISASM_LINK |
		DISASM_ORIG_REG, DISASM_REG | DISASM_IND, 0);
	set_instruction_other(cw->instructions + 2, 4, 5, st_function);
	set_instruction_base(cw->instructions + 3, 4, "add", 1);
	set_instruction_args(cw->instructions + 3, DISASM_REG | DISASM_LINK |
		DISASM_ORIG_REG, DISASM_REG | DISASM_LINK | DISASM_ORIG_REG, DISASM_REG
		| DISASM_LINK | DISASM_ORIG_REG);
	set_instruction_other(cw->instructions + 3, 4, 10, add_function);
	set_instruction_base(cw->instructions + 4, 5, "sub", 1);
	set_instruction_args(cw->instructions + 4, DISASM_REG | DISASM_LINK |
		DISASM_ORIG_REG, DISASM_REG | DISASM_LINK | DISASM_ORIG_REG,
		DISASM_REG | DISASM_LINK | DISASM_ORIG_REG);
	set_instruction_other(cw->instructions + 4, 4, 10, sub_function);
	load_instructions_1(cw);
}
