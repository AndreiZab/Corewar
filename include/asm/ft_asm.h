#ifndef FT_ASM_H
# define FT_ASM_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "libft.h"
# include "op.h"

typedef struct		s_data
{
	char				*name;
	char				*comment;

	int					fd;
	int					num_current_row;
	unsigned int		comm_counter;
	int					code_size;

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

#endif