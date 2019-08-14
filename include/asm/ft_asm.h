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
	Inderect_label,
	Direct_label,
	Instruction,
	Line_feed,
	Separator,
	Indirect,
	Register,
	Command,
	Direct,
	String,
	Label,
	EOF
}	t_type;

typedef struct	s_ops
{
	char			*name;
	unsigned char	code;
	unsigned char	args_num;
	bool			args_types_code;
	char			args_types[3];
	unsigned char	t_dir_size;
}				t_ops;


const t_ops	g_op_tab[REG_NUMBER];

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
	int					fd;
	int					x;
	int					y;
//	char 				*processing_row;
	char				quotes;
	struct s_label		*labels;
}					t_data;

t_data		*g_data;

typedef struct		s_label
{
	char				*name;
	t_token				*ptr;

	struct s_label		*next;
	struct s_label		*prev;
}					t_label;



/*
** parse_asm.c
 */

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
//void	ft_add_newline_token(void);

/*
** syntax_analysis.c
 */

//int			ft_is_command(char *str);
//void		ft_syntax_analysis(void);

/*
** syntax_analysis_helper.c
 */

//void	ft_validate_label(t_type type);
//int 	ft_is_argument(t_type type);

#endif