#ifndef FT_ASM_H
# define FT_ASM_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "libft.h"
# include "op.h"

# define T_REGS 1
# define T_DIRS 10
# define T_INDS 100

typedef enum
{
	Direct_number,
	Direct_label,
	Whitespace,
	Label_arg,
	Line_feed,
	Separator,
	Register,
	Command,
	Number,
	Label
}	t_type;

typedef struct			s_token
{
	char				*content;
	t_type				type;
	unsigned			row;
	struct s_token		*next;
}						t_token;

typedef struct		s_data
{
	char				*name;
	char				*comment;
	t_token				*tokens;
	int					fd;
	int					num_current_row;
	int					count_char;
	unsigned int		comm_counter;
	int					code_size;
	char				quotes;

	struct s_command	*comms;
	struct s_label		*labels;
}					t_data;

typedef struct		s_command
{
	int					opcode;
	int					argc;
	int					*argv;

	struct s_command 	*next;
}					t_command;

typedef struct		s_label
{
	char				*name;
	int					line;

	struct s_label		*next;
}					t_label;


/*
** parse_asm.c
 */

void		ft_asm(char *str);

/*
** asm.c
 */

void		ft_error(char *str, t_data *data);

/*
** row_is_code.c
 */

void		ft_row_is_code (t_data *data, char *str);
void	ft_add_newline_token(t_data *data);

/*
** syntax_analysis.c
 */

int			ft_is_command(char *str);
void		ft_syntax_analysis(t_data *data);

#endif