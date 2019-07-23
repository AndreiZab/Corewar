#include "ft_cw.h"

void	ft_map_set_byte(t_corewar *cw, int pos, unsigned char value)
{
	pos = pos % MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	cw->map[pos] = value;
}

void	ft_map_set_word(t_corewar *cw, int pos, short value)
{
	unsigned char	*val;

	val = (unsigned char*)&value;
	ft_map_set_byte(cw, pos, val[0]);
	ft_map_set_byte(cw, pos + 1, val[1]);
}

void	ft_map_set_dword(t_corewar *cw, int pos, long value)
{
	unsigned char	*val;

	val = (unsigned char*)&value;
	ft_map_set_byte(cw, pos, val[0]);
	ft_map_set_byte(cw, pos + 1, val[1]);
	ft_map_set_byte(cw, pos + 2, val[2]);
	ft_map_set_byte(cw, pos + 3, val[3]);
}