#ifndef FT_ASM_H
# define FT_ASM_H
# include "../../lib/libft.h"
# include "../op.h"

typedef struct	s_asm
{
	char				*name;
	char				*comment;

	unsigned int		comm_counter;

	struct s_command	*comms;
	struct s_label		*labels;
}				t_asm;

typedef struct	s_command
{
	int		opcode;
	int		argc;
	int		*argv;

	struct s_command *next; 
}				t_command;

typedef struct	s_label
{
	char	*name;
	int		line;

	struct s_label *next;
}				t_label;


#endif