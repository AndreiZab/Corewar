#include "ft_cw.h"
#include <stdio.h>

static char		*ft_reverse_bytes(char *src, int size)
{
	char	buff;
	int		i;

	if (src == NULL)
		return (NULL);
	i = -1;
	while (++i < size / 2)
	{
		buff = src[size - 1 - i];
		src[size - 1 - i] = src[i];
		src[i] = buff;
	}
	return (src);
}

static int		ft_exe_read_data(t_corewar *cw, int fd)
{
	char	buffer[MAX(COMMENT_LENGTH, CHAMP_MAX_SIZE) + 1];
	unsigned int		supp;

	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	if (*((int*)ft_reverse_bytes(buffer, 4)) != COREWAR_EXEC_MAGIC)
		return (FT_EXE_MAGIC);
	if (ft_accurate_read(fd, buffer, PROG_NAME_LENGTH) != FT_OK)
		return (FT_READ_FILE);
	cw->players->name = ft_strdup(buffer);
	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	if (*((int*)buffer) != 0x00000000)
		return (FT_4_NULL);
	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	supp = *((unsigned int*)(ft_reverse_bytes(buffer, 4)));
	if (supp > CHAMP_MAX_SIZE)
		return (FT_EXE_MAX);
	cw->players->exe_size = supp;
	if (ft_accurate_read(fd, buffer, COMMENT_LENGTH) != FT_OK)
		return (FT_READ_FILE);
	cw->players->comment = ft_strdup(buffer);
	if (ft_accurate_read(fd, buffer, 4) != FT_OK)
		return (FT_READ_FILE);
	if (*((int*)buffer) != 0x00000000)
		return (FT_4_NULL);
	if (ft_accurate_read(fd, buffer, cw->players->exe_size) != FT_OK)
		return (FT_READ_FILE);
	if ((cw->players->exe = (char*)malloc(sizeof(char) * cw->players->exe_size)) == NULL)
		return (FT_MEMORY);
	ft_memcpy(cw->players->exe, buffer, cw->players->exe_size);
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