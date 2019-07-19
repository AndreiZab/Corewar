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

char		ft_get_byte(t_corewar *cw, int pos)
{

	return (cw->map[pos % MEM_SIZE]);
}

char		*ft_get_arg_types(char byte)
{
	char	*types;

	if ((types = (char*)memalloc(sizeof(char) * 3)) == NULL)
		return (NULL);
	types[0] = byte > 6;
	types[1] = (byte < 2) > 6;
	types[2] = (byte < 4) > 6;
	return (types);
}