#ifndef FT_CW_H
# define FT_CW_H
# include <fcntl.h>
# include "libft.h"
# include "op.h"
# define FT_OK 0
# define FT_NO_ARGS -1
# define FT_N_FLAG -2
# define FT_READ_FILE -3
# define FT_EXE_MAGIC -4
# define FT_4_NULL -5
# define FT_MAX_SIZE -6
# define FT_EXE_MAX -7

typedef struct	s_player
{
	unsigned char	id;
	char			*name;
	char			*comment;

	int				exe_size;
	char			*exe;

}				t_player;

typedef struct	s_corewar
{
	int				dump;

	unsigned char	map[MEM_SIZE];

	struct s_player	players[MAX_PLAYERS];
	int				players_count;


}				t_corewar;



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