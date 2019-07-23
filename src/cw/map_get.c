#include "ft_cw.h"

unsigned char	ft_map_get_byte(t_corewar *cw, int pos)
{
	pos = pos % MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	return (cw->map[pos]);
}

short			ft_map_get_word(t_corewar *cw, int pos)
{
	char	val;
	short	word;

	//Возможно инвертировать pos и pos + 1
	word = 0;
	val = ft_map_get_byte(cw, pos);
	ft_memcpy(&word, &val, 1);
	val = ft_map_get_byte(cw, pos + 1);
	ft_memcpy((char*)(&word) + 1, &val, 1);
	return (word);
}

long			ft_map_get_dword(t_corewar *cw, int pos)
{
	char	val;
	long	dword;

	//Возможно инвертировать pos и pos + 1
	dword = 0;
	val = ft_map_get_byte(cw, pos);
	ft_memcpy(&dword, &val, 1);
	val = ft_map_get_byte(cw, pos + 1);
	ft_memcpy((char*)(&dword) + 1, &val, 1);
	val = ft_map_get_byte(cw, pos + 2);
	ft_memcpy((char*)(&dword) + 2, &val, 1);
	val = ft_map_get_byte(cw, pos + 3);
	ft_memcpy((char*)(&dword) + 3, &val, 1);
	return (dword);
}
