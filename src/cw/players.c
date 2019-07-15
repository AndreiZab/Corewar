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

void		ft_player_delete(t_player **player)
{
	t_player	*next;

	if (player == NULL || *player == NULL)
		return ;
	next = (*player)->next;
	// if ((*player)->name)
	// 	free((*player)->name);
	// if ((*player)->comment)
	// 	free((*player)->comment);
	// if ((*player)->exe)
	// 	free((*player)->exe);
	// free(*player);
	//*player = next;
}