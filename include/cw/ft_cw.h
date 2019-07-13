#ifndef FT_CW_H
# define FT_CW_H
# include "libft.h"
# include "op.h"

typedef struct	s_corewar
{
	unsigned char	map[MEM_SIZE];

	t_player		players[MAX_PLAYERS];
	int				players_count;


}				t_corewar;

typedef struct	s_player
{
	char	id;

}				t_player;

typedef struct	s_carriage
{
	char			player_id;

	unsigned int	rg[REG_NUMBER];
	char			carry;
	char			live;

	unsigned int	pc; //program counter
	int				command; //?
	unsigned int	preparing_ticks;

}				t_carriage;


t_corewar	*ft_cw_alloc(void);
void		ft_cw_free(t_corewar **cw);

void		ft_map_set(t_corewar *cw, int pos, char val);
void		ft_map_get(t_corewar *cw, int pos);

#endif