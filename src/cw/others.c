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
