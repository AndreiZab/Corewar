#ifndef FT_ASM_H
# define FT_ASM_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "libft.h"
# include "op.h"

# include <stdbool.h>	// можно или сделать enum?

//# define T_REGS 1
//# define T_DIRS 10
//# define T_INDS 100

typedef enum	e_type
{
	Register = 1,
	Direct,
	Direct_label,
	Indirect,
	Indirect_label,
	Command,
	Label,
	Instruction,
	Separator,
	Line_feed,
	EOF
}	t_type;

typedef struct	s_ops
{
	char			*name;
	unsigned int	code;
	unsigned int	args_num;
	bool			args_types_code;
	unsigned int	args_types[3];
	unsigned int	t_dir_size;
}				t_ops;


typedef struct			s_token
{
	int					x;
	int					y;
	u_int32_t			bytes;
	char				*content;
	t_type				type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct		s_data
{
	char				*name;
	char				*comment;
	t_token				*tokens;
	char				*output;
	int					fd;
	char				*filename;
	int					x;
	int					y;
	char				quotes;
	struct s_label		*labels;
}					t_data;

t_data		*g_data;
u_int32_t	g_bytes;

typedef struct		s_label
{
	t_token				*ptr;

	struct s_label		*next;
	struct s_label		*prev;
}					t_label;



/*
** parse_asm.c
 */

void		ft_free_data(void);
void		ft_asm(char *str);

/*
** asm.c
 */

void		ft_error(char *str);

/*
** row_is_code.c
 */

void		ft_token_create(t_type type);
void		ft_row_is_code (char *str);

/*
** syntax_analysis.c
 */

void 		ft_syntax_champ(void);

/*
** compilation.c
 */

void	 	ft_compilation_champ(void);

/*
** write_bytes.c
 */

void		ft_write_bytes(void);

/*
** tools.c
 */

void		ft_revert_tokens(void);
void		ft_free_data(void);
void		ft_create(int fd, char *str);
void		ft_token_create(t_type type);

/*
**
 */

static t_ops			g_op_tab[16] = {
		{
				.name = "live",
				.code = 0x01,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 4,
		},
		{
				.name = "ld",
				.code = 0x02,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.t_dir_size = 4,
		},
		{
				.name = "st",
				.code = 0x03,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_REG, T_REG | T_IND, 0},
				.t_dir_size = 4,
		},
		{
				.name = "add",
				.code = 0x04,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "sub",
				.code = 0x05,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "and",
				.code = 0x06,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "or",
				.code = 0x07,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "xor",
				.code = 0x08,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "zjmp",
				.code = 0x09,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
		},
		{
				.name = "ldi",
				.code = 0x0A,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.t_dir_size = 2,
		},
		{
				.name = "sti",
				.code = 0x0B,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
				.t_dir_size = 2,
		},
		{
				.name = "fork",
				.code = 0x0C,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
		},
		{
				.name = "lld",
				.code = 0x0D,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.t_dir_size = 4,
		},
		{
				.name = "lldi",
				.code = 0x0E,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.t_dir_size = 2,
		},
		{
				.name = "lfork",
				.code = 0x0F,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
		},
		{
				.name = "aff",
				.code = 0x10,
				.args_num = 1,
				.args_types_code = true,
				.args_types = {T_REG, 0, 0},
				.t_dir_size = 4,
		}
};

#endif