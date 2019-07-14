#include "ft_cw.h"

static int		ft_exe_read_data(t_corewar *cw, int fd)
{
	char	buffer[MAX(COMMENT_LENGTH, CHAMP_MAX_SIZE) + 1];

	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	if ((int)(*buffer) != COREWAR_EXEC_MAGIC)
		return (FT_EXE_MAGIC);
	if (ft_accurate_read(fd, buffer, PROG_NAME_LENGTH) != FT_OK)
		return (FT_READ_FILE);
	cw->players->name = ft_strdup(buffer);
	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	if ((int)(*buffer) != 0x00000000)
		return (FT_4_NULL);
	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	if ((int)(*buffer) > CHAMP_MAX_SIZE)
		return (FT_EXE_MAX);
	cw->players->exe_size = (int)(*buffer);
	if (ft_accurate_read(fd, buffer, COMMENT_LENGTH) != FT_OK)
		return (FT_READ_FILE);
	cw->players->comment = ft_strdup(buffer);
	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	if ((int)(*buffer) != 0x00000000)
		return (FT_4_NULL);
	if (ft_accurate_read(fd, buffer, cw->players->exe_size) != FT_OK)
		return (FT_READ_FILE);
	cw->players->exe = ft_strdup(buffer);
	if (ft_accurate_read(fd, buffer, 1) != FT_READ)
		return (FT_TRASH_AFTER_BINARY_DATA);
	return (FT_OK);
}

static int		ft_validate_binary(char *data, int data_size)
{
	return (FT_OK);
}

int				ft_exe_read(t_corewar *cw, char *filename)
{
	int	fd;
	int err;

	if ((fd = open(filename, O_RDONLY)) <= 0)
		return (FT_READ_FILE);
	err = ft_exe_read_data(cw, fd);
	if (err == FT_OK)
		err = ft_validate_binary(cw->players->exe, cw->players->exe_size);
	if (err == FT_OK)
	{
		++(cw->players_count);
		ft_player_new(&cw->players);
	}
	close(fd);
	return (err);
}