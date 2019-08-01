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
# define FT_DUMP_ROW_SIZE 32
# define FT_LINK 4
# define FT_IDX_USE 8

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

	int				live;
	char			dead;

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
	char			aff;
	char			pinfo;

	int				cycles_to_die;
	int				next_check;
	int				cycle;
	unsigned char	*map;

	int				dir_size;

	struct s_player	*players;
	int				players_count;

	struct s_carriage		*carriages;

	struct s_arg_handler	*argh;
	struct s_arg_handler	*argh_default;

	struct s_comm_handler	*commh;
	struct s_comm_handler	*commh_default;
}				t_corewar;



typedef struct	s_carriage
{
	int					player_id;

	unsigned int		rg[REG_NUMBER];
	char				carry;
	int					cycle_live;

	char				*arg_types;
	char				dead;
	int					arg[3];

	unsigned int		pc; //program counter
	unsigned int		pc_comm; // позиция исполняемой команды. Удобно для indirect
	int					command; //?
	unsigned int		preparing_ticks;

	struct s_carriage *next;
}				t_carriage;

typedef struct	s_arg_handler
{
	char					*on_arg;
	int						(*f)
		(t_corewar *cw, int argc, char **argv, int *arg_i);
	struct s_arg_handler	*next;
}				t_arg_handler;

typedef struct	s_comm_handler
{
	char	comm;
	int		cycles;
	int		(*f)(t_corewar *cw, t_carriage *carr);
	struct		s_comm_handler *next;
}				t_comm_handler;


/*
** cw.c
*/

t_corewar	*ft_cw_alloc(int *err);
void		ft_cw_free(t_corewar **cw);

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
int	ft_process_flag_a(t_corewar *cw, int argc, char **argv, int *arg_i);
int ft_process_flag_dump(t_corewar *cw, int argc, char **argv, int *arg_i);
int	ft_process_flag_n(t_corewar *cw, int argc, char **argv, int *arg_i);
int ft_process_file(t_corewar *cw, int argc, char **argv, int *arg_i);

/*
**	arg_process_2.c
*/

int ft_process_flag_pinfo(t_corewar *cw, int argc, char **argv, int *arg_i);


int		ft_tick(t_corewar *cw);


/*
**	kill_machine.c
*/

void	ft_kill_machine(t_corewar *cw, int *play);


/*
** map_set.c
*/

void	ft_map_set_byte(t_corewar *cw, int pos, unsigned char value);
void	ft_map_set_word(t_corewar *cw, int pos, short value);
void	ft_map_set_dword(t_corewar *cw, int pos, long value);


/*
** map_get.c
*/

unsigned char	ft_map_get_byte(t_corewar *cw, int pos);
short			ft_map_get_word(t_corewar *cw, int pos);
long			ft_map_get_dword(t_corewar *cw, int pos);


/*
** players.c
*/

t_player	*ft_player_new(t_player **players);
void		ft_player_delete(t_player **player);
t_player	*ft_player_by_id(t_player *players, int id);
void		ft_player_list_free(t_player **players);


/*
** carriage.c
*/

t_carriage	*ft_carriage_new(t_carriage **carrs, int player_id, int pos);
void		ft_carr_move(t_carriage *carr, int move);
void		ft_carr_load_arg_types(t_corewar *cw, t_carriage *carr);
void		ft_carriage_list_free(t_carriage **carrs);


/*
** carr_load.c
*/

void	ft_carr_load_dir(t_corewar *cw, t_carriage *carr, int arg_n);
void	ft_carr_load_ind_link(t_corewar *cw, t_carriage *carr, int arg_n);
void	ft_carr_load_ind(t_corewar *cw, t_carriage *carr, int arg_n, char idx);
void	ft_carr_load_reg_link(t_corewar *cw, t_carriage *carr, int arg_n);
void	ft_carr_load_reg(t_corewar *cw, t_carriage *carr, int arg_n);
void	ft_carr_load_value(t_corewar *cw, t_carriage *carr, int arg_n,
			char value_type);

/*
** commh.c
*/

int		ft_commh_add(t_comm_handler **commh, char command, int cycles,
			int (*f)(t_corewar *cw, t_carriage *carr));
t_comm_handler	*ft_commh_by_byte(t_corewar *cw, char command);
void	ft_commh_free(t_comm_handler **comm_h);


/*
** accurate_reader.c
*/

int 		ft_accurate_read(int fd, char *buffer, int n_bytes);


/*
** exe_reader.c
*/

int			ft_exe_read(t_corewar *cw, char *filename);

/*
** casting_uc_hex.c
*/

char		*casting_uc_hex(int num, int width);


/*
** dump.c
*/

int ft_show_dump(t_corewar *cw);


/*
** others.c
*/

int			ft_contains_ids(t_corewar *cw, int id);
void		ft_set_ids(t_corewar *cw);
char		ft_get_byte(t_corewar *cw, int pos);
unsigned char	*ft_get_arg_types(unsigned char byte);
void		ft_show_players(t_corewar *cw);
int			ft_regnumber_contains(int num);


/*
** bandles.c 
*/

void	ft_bandle_args(t_corewar *cw);
void	ft_bandle_commands(t_corewar *cw);


/*
** comm_process.c
*/

int		ft_comm_live(t_corewar *cw, t_carriage *carr);
int		ft_comm_ld(t_corewar *cw, t_carriage *carr);
int		ft_comm_st(t_corewar *cw, t_carriage *carr);
int		ft_comm_add(t_corewar *cw, t_carriage *carr);
int		ft_comm_sub(t_corewar *cw, t_carriage *carr);
int		ft_comm_and(t_corewar *cw, t_carriage *carr);
int		ft_comm_or(t_corewar *cw, t_carriage *carr);
int		ft_comm_xor(t_corewar *cw, t_carriage *carr);
int		ft_comm_zjmp(t_corewar *cw, t_carriage *carr);
int		ft_comm_ldi(t_corewar *cw, t_carriage *carr);
int		ft_comm_sti(t_corewar *cw, t_carriage *carr);
int		ft_comm_fork(t_corewar *cw, t_carriage *carr);
int		ft_comm_lld(t_corewar *cw, t_carriage *carr);
int		ft_comm_lldi(t_corewar *cw, t_carriage *carr);
int		ft_comm_lfork(t_corewar *cw, t_carriage *carr);
int		ft_comm_aff(t_corewar *cw, t_carriage *carr);
int		ft_comm_unknown(t_corewar *cw, t_carriage *carr);

#endif