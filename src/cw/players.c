#include "ft_cw.h"

t_player	*ft_player_new(t_player **players)
{
	t_player	*player;

	if (players == NULL)
		return (NULL);
	if ((player = (t_player*)ft_memalloc(sizeof(t_player))) == NULL)
		return (NULL);
	player->next = *players;
	*players = player;
	return (player);
}