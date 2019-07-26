#include "ft_cw.h"

int			ft_contains_ids(t_corewar *cw, int id)
{
	t_player	*player;

	player = cw->players->next;
	while (player)
	{
		if (id == player->id)
			return (1);
		player = player->next;
	}
	return (0);
}

void		ft_set_ids(t_corewar *cw)
{
	int id;
	t_player	*pl;

	pl = cw->players;
	id = cw->players_count;
	while (id != 0 && pl)
	{
		if (ft_contains_ids(cw, id))
			--id;
		else if (pl->id != 0)
			pl = pl->next;
		else
		{
			pl->id = id--;
			pl = pl->next;
		}
	}
}

// char		ft_get_byte(t_corewar *cw, int pos)
// {

// 	return (cw->map[pos % MEM_SIZE]);
// }

// char		*ft_get_bytes(t_corewar *cw, int pos, int count, char reverse)
// {
// 	char	*bytes;
// 	int		i;

// 	if ((bytes = (char*)ft_memalloc(sizeof(char) * count)) == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (++i < count)
// 		if (reverse)
// 			bytes[count - 1 - i] = ft_get_byte(cw, pos + i);
// 		else
// 			bytes[i] = ft_get_byte(cw, pos + i);
// 	return (bytes);
// }

unsigned char	*ft_get_arg_types(unsigned char byte)
{
	unsigned char	*types;

	if ((types = (unsigned char*)ft_memalloc(sizeof(char) * 3)) == NULL)
		return (NULL);
	types[0] = byte >> 6;
	types[1] = (byte & 0b00110000) >> 4;
	types[2] = (byte & 0b00001100) >> 2;
	// ft_putstr("ARGTYPES[");
	// ft_putnbr(types[0]);
	// ft_putchar(' ');
	// ft_putnbr(types[1]);
	// ft_putchar(' ');
	// ft_putnbr(types[2]);
	// ft_putstr("]\n");
	return (types);
}

void		ft_show_players(t_corewar *cw)
{
	t_player	*pl;
	int			id;

	id = 0;
	ft_putstr("Introducing contestants...\n");
	while (++id <= cw->players_count)
	{
		pl = ft_player_by_id(cw->players, id);
		ft_putstr("* Player ");
		ft_putnbr(id);
		ft_putstr(", weighing ");
		ft_putnbr(pl->exe_size);
		ft_putstr(" bytes, \"");
		ft_putstr(pl->name);
		ft_putstr("\" (\"");
		ft_putstr(pl->comment);
		ft_putstr("\") !\n");
	}
}