/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:56:05 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/17 11:57:42 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "op.h"
# define DISASM_REG 1
# define DISASM_DIR 2
# define DISASM_IND 4
# define DISASM_COL_FILENAME cc_green
# define DISASM_COL_ERROR cc_red
# define DISASM_COL_NAME cc_cyan
# define DISASM_COL_WARNING cc_yellow
# define DISASM_COL_INSTRUCTION cc_blue
# define DISASM_OPT_COLORS 1
# define DISASM_OPT_FILE_FORMAT 2
# define DISASM_OPT_FILENAME 4

typedef struct	s_instruction
{
	char					*name;
	unsigned char			byte;
	char					type_byte;
	int						argc;
	char					argt[3];
	char					types[3];
	int						dir_size;

	struct s_instruction	*next;
}				t_instruction;

typedef struct	s_exe
{
	t_instruction	*insts;

	unsigned char	*data;
	int				size;
}				t_exe;

/*
** print_1.c, print_2.c, print_3.c
*/

void			print_filename(char *filename, char options);
int				print_error(char *str, char options);
void			print_name(char *str, char options);
void			print_code_size(int nbr, char options);
void			print_warning(char *str, char options);

void			print_comment(char *str, char options);
int				print_error_unknown_inst(unsigned char byte, char options);
int				print_error_inst(char *inst, char *str, char options);

int				print_usage(void);
void			print_args(t_exe *exe, t_instruction *inst, int i,
					char options);

/*
** print_utils.c
*/

void			print_col_str(char *str, char options, t_ccolor col);

/*
** check_1.c, check_2.c, check_3.c
*/

int				check_magic_header(int fd, char options, void *arg);
int				check_name(int fd, char options, void *arg);
int				check_null(int fd, char options, void *arg);
int				check_code_size(int fd, char options, void *arg);
int				check_comment(int fd, char options, void *arg);

int				check_instruction(t_exe *exe, t_instruction *inst, int i,
					char options);

int				check_exe(int fd, char options, void *arg);
int				check_eof(int fd, char options, void *arg);

/*
** load_inst.c
*/

int				load_instructions(t_exe *exe);

/*
** utils.c
*/

int				accurate_read(int fd, char *buffer, int n_bytes);
int				end_with(char *str, char *end);
void			revert_bytes(void *addr, int size);
int				inst_add(t_instruction **root, char *name, char byte,
					char type_byte);
t_instruction	*inst_find(t_instruction *root, unsigned char byte);

#endif
