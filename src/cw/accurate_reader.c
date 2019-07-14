#include "ft_cw.h"

/* 
** RU
** Модуль Accurate Reader:
** Предназначен для гарантированного чтения n-байтов из потока
*/

int ft_accurate_read(int fd, char *buffer, int n_bytes)
{
	int readed;
	int i;
	int	no_data;

	if (fd <= 0)
		return (FT_READ);
	no_data = 0;
	i = 0;
	while (i != n_bytes)
	{
		readed = read(fd, buffer + i, n_bytes - i);
		if (readed == 0)
		{
			++no_data;
			if (no_data == FT_ACCURATE_READ_MAX_WAIT)
				return (FT_READ);
		}
		else if (readed < 0)
			return (FT_READ);
		else
			i += readed;
	}
	return (FT_OK);
}
