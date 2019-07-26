#include "ft_cw.h"

int ft_show_dump(t_corewar *cw)
{
	int		i;
	int		j;
	char	*byte;

	i = -1;
	while (++i * FT_DUMP_ROW_SIZE < MEM_SIZE)
	{
		ft_putstr("0x");
		byte = casting_uc_hex(i * FT_DUMP_ROW_SIZE, 4);
		ft_putstr(byte);
		free(byte);
		ft_putstr(" :");
		j = 0;
		while (j < FT_DUMP_ROW_SIZE && j + i * FT_DUMP_ROW_SIZE < MEM_SIZE)
		{
			if ((byte = casting_uc_hex(cw->map[j + i * FT_DUMP_ROW_SIZE], 2))
					== NULL)
				return (FT_MEMORY);
			ft_putchar(' ');
			ft_putstr(byte);
			free(byte);
			++j;
		}
		ft_putchar('\n');
	}
	return (FT_OK);
}
