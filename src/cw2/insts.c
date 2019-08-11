#include "corewar.h"

t_instruction	*insts_find(t_corewar *cw, unsigned char byte)
{
	int		i;

	i = -1;
	while (++i < COREWAR_INSTRUCTIONS_COUNT)
		if (cw->instructions[i].byte == byte)
			return (cw->instructions + i);
	return (NULL);
}