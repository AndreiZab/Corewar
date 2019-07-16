#ifndef FT_CW_H
# define FT_CW_H
# include <stdlib.h>
# include <unistd.h>
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
# define FT_MEMORY -8
# define FT_NULL -9
# define FT_ARG -10
# define FT_READ -11
# define FT_TRASH_AFTER_BINARY_DATA -12
# define FT_NO_PLAYERS -13
# define MAX(x, y) ((x > y) ? x : y)

/*
** Определяет число безрезультатных чтений (read return 0)
**  после которого чтение прекратится с ошибкой
*/

# define FT_ACCURATE_READ_MAX_WAIT 10

typedef struct	s_player
{
	int				id;	//Переделать под uint
	char			*name;
	char			*comment;

	int				exe_size;
	char			*exe;

	struct s_player *prev;
	struct s_player	*next;

}				t_player;

typedef struct	s_corewar
{
	char			dump_mode;
	int	dump_cycle; //переделать под ulonglongint

	char			v;

	unsigned char	*map;

	struct s_player	*players;
	int				players_count;

	struct s_arg_handler	*argh;
	struct s_arg_handler	*argh_default;
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

typedef struct	s_arg_handler
{
	char					*on_arg;
	int						(*f)
		(t_corewar *cw, int argc, char **argv, int *arg_i);
	struct s_arg_handler	*next;
}				t_arg_handler;


void		ft_cw_free(t_corewar **cw);

void		ft_map_set(t_corewar *cw, int pos, char val);
void		ft_map_get(t_corewar *cw, int pos);

/*
**	argh.c
*/

int		ft_argh_add(t_arg_handler **arg_h, char *on_arg,
			int (*f)(t_corewar *cw, int argc, char **arg, int *arg_i));
int		ft_argh_do(t_corewar *cw, int argc, char **argv, int *arg_i);
void	ft_argh_free(t_arg_handler **arg_h);

/*
**	arg_process.c
*/

int	ft_process_flag_v(t_corewar *cw, int argc, char **argv, int *arg_i);
int ft_process_flag_dump(t_corewar *cw, int argc, char **argv, int *arg_i);
int	ft_process_flag_n(t_corewar *cw, int argc, char **argv, int *arg_i);
int ft_process_file(t_corewar *cw, int argc, char **argv, int *arg_i);

/*
** players.c
*/

t_player	*ft_player_new(t_player **players);
void		ft_player_delete(t_player **player);
void		ft_player_list_start(t_player **players);


/*
** accurate_reader.c
*/

int 		ft_accurate_read(int fd, char *buffer, int n_bytes);


/*
** exe_reader.c
*/

int			ft_exe_read(t_corewar *cw, char *filename);


/*
** others.c
*/

int			ft_contains_ids(t_corewar *cw, int id);
void		ft_set_ids(t_corewar *cw);

#endif