#include "ft_cw.h"

int		ft_msg(char *str, int err)
{
	ft_putstr(str);
	return (err);
}

int		ft_read_champ(t_corewar *cw, char *filename, char id, int *champ_i)
{
	int		fd;
	char	buffer[CHAMP_MAX_SIZE + COMMENT_LENGTH];
	int		readed;

	if ((fd = open(filename, O_RDONLY)) <= 0)
		return (ft_msg("Err: can't open file\n", FT_READ_FILE));
	//accurate reader?
	readed = read(fd, buffer, 4);
	if ((int)(*buffer) != COREWAR_EXEC_MAGIC)
		return (ft_msg("Err: Not a binary file\n", FT_EXE_MAGIC));
	readed = read(fd, buffer, PROG_NAME_LENGTH);
	buffer[readed] = '\0';
	cw->players[*champ_i].name = ft_strdup(buffer);
	readed = read(fd, buffer, 4);
	if ((int)(*buffer) != 0x000000)
		return (ft_msg("Err: 4 null bytes ecpected\n", FT_4_NULL));
	readed = read(fd, buffer, 4);
	cw->players[*champ_i].exe_size = (int)(*buffer);
	if ((int)(*buffer) < 0 || (int)(*buffer) > CHAMP_MAX_SIZE)
		return (ft_msg("Err: exe max size\n", FT_EXE_MAX));
	readed = read(fd, buffer, COMMENT_LENGTH);
	cw->players[*champ_i].comment = ft_strdup(buffer);
	readed = read(fd, buffer, 4);
	if ((int)(*buffer) != 0x000000)
		return (ft_msg("Err: 4 null bytes ecpected\n", FT_4_NULL));
	readed = read(fd, buffer, cw->players[*champ_i].exe_size);
	cw->players[*champ_i].exe = (char*)malloc(cw->players[*champ_i].exe_size);
	ft_memcpy(cw->players[*champ_i].exe, buffer, cw->players[*champ_i].exe_size);
	cw->players[*champ_i].id = id;
	++(*champ_i);
	close(fd);
	return (FT_OK);
}

/*
** n = -2  флаг n не ожидается
** n = -1  флаг n ожидается 
** Любое другое значение - значение флага n
*/


//-dump ннада
int		ft_process_args(t_corewar *cw, int argc, char **argv)
{
	int		i;
	int		n;
	int		champ_i;

	if (argc == 1)
		return (ft_msg("Err: No args!", FT_NO_ARGS));
	champ_i = 0;
	n = -2;
	i = 0;
	while (++i < argc)
	{
		if (n == -1)
		{
			if (ft_isint(argv[i]))
			{
				n = ft_atoi(argv[i]);
				if (n <= 0 || n > 255)
					return (ft_msg("Err: -n number must be highest 0\n", FT_N_FLAG));
			}
			else
				return (ft_msg("Err: After -n expected number\n", FT_N_FLAG));
		}
		else
		{
			if (ft_strcmp(argv[i], "-n") == 0)
				n = -1;
			else
			{
				ft_read_champ(cw, argv[i], (n == -2 ? 0 : n), &champ_i);
			}
		}
	}	
	return (FT_OK);
}