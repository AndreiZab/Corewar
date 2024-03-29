/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 11:41:11 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/23 11:02:23 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"
# include "SDL.h"
# include "SDL_ttf.h"
# include "op.h"
# define COREWAR_STATUS_OK 0
# define COREWAR_STATUS_WARNING 1
# define COREWAR_STATUS_FINISH 2
# define COREWAR_STATUS_FATAL -1
# define COREWAR_OPT_COLORS 1
# define COREWAR_OPT_VISUALIZER 2
# define COREWAR_OPT_AFF 4
# define COREWAR_OPT_DUMP_INFO 8
# define COREWAR_OPT_LOG_LIVES 1
# define COREWAR_OPT_LOG_CYCLES 2
# define COREWAR_OPT_LOG_OPERATIONS 4
# define COREWAR_OPT_LOG_DEATHS 8
# define COREWAR_OPT_LOG_PC_MOVEMENTS 16
# define COREWAR_OPT_LOG_ORIGINAL 32
# define COREWAR_COLOR_ERROR cc_red
# define COREWAR_COLOR_FILENAME cc_cyan
# define COREWAR_COLOR_CYCLE cc_cyan
# define COREWAR_COLOR_DIE_STEP cc_yellow
# define COREWAR_COLOR_PLAYER cc_yellow
# define COREWAR_COLOR_CARRIAGE cc_magenta
# define COREWAR_COLOR_INSTRUCTION cc_blue
# define COREWAR_COLOR_ADDRESS cc_green
# define COREWAR_CHECKS_COUNT 8
# define COREWAR_INSTRUCTIONS_COUNT 16
# define DISASM_REG 1
# define DISASM_DIR 2
# define DISASM_IND 4
# define DISASM_LINK 8
# define DISASM_ORIG_REG 16
# define DISASM_ORIG_VALUE_IN 32
# define DISASM_IDX 64
# define COREWAR_LINK 4
# define COREWAR_IDX 8
# define COREWAR_DUMP_COLUMNS 32

# define COURIER_TTF "/Library/Fonts/Courier New Bold.ttf"
# define BLK 0, 0, 0, 0
# define RD 170, 0, 0, 0
# define GRN 0, 170, 0, 0
# define BL 0, 0, 255, 0
# define WHT 255, 255, 255, 0
# define YLW 170, 170, 0, 0
# define GRY 127, 127, 127, 0

# define BLK_COL -1
# define WHT_COL 0
# define RD_COL 1
# define GRN_COL 2
# define BL_COL 3
# define YLW_COL 4

typedef struct s_corewar		t_corewar;

typedef struct s_player			t_player;

typedef struct s_instruction	t_instruction;

typedef struct s_carriage		t_carriage;

struct							s_player
{
	char			set;

	char			*name;
	char			*comment;
	unsigned char	*code;
	int				size;

	int				live;
	char			dead;
};

struct							s_instruction
{
	char			*name;

	unsigned char	byte;
	char			type_byte;
	int				argc;
	char			argt[3];
	int				dir_size;
	int				sleep;
	int				(*f)(t_corewar*, t_carriage*);
};

struct							s_carriage
{
	int				id;
	unsigned char	owner_id;
	char			carry;
	int				rg[REG_NUMBER];
	int				pc;
	int				pc_comm;
	int				sleep;
	t_instruction	*instruction;
	int				live_cycle;
	int				lives;
	char			dead;
	t_carriage		*next;
};

struct							s_corewar
{
	char			options;
	char			log;
	int				dump;

	int				(*checks[COREWAR_CHECKS_COUNT])
			(int, t_corewar*, t_player*);
	t_instruction	instructions[COREWAR_INSTRUCTIONS_COUNT];
	char			*current_filename;

	t_player		players[MAX_PLAYERS];
	int				players_count;
	int				next_id;

	unsigned char	map[MEM_SIZE];
	unsigned char	players_map[MEM_SIZE];

	char			temp_types[3];
	int				args[3];

	t_carriage		*carrs;

	int				cycle;
	int				cycle_to_die;
	int				die_step;
	int				cycle_lives_counter;

	t_player		*winner;

	SDL_Window		*win;
	SDL_Renderer	*ren;
	TTF_Font		*fnt;
	int				scr_w;
	int				scr_h;
	int				fnt_h;
	int				col;
	int				xl;
	int				xr;
	int				yu;
	int				yd;
};

/*
** corewar_memory.c
*/

t_corewar						*corewar_init(int *status);
void							corewar_free(t_corewar **corewar);

/*
** process_arguments.c
*/

int								process_arguments(t_corewar *cw, int argc,
		char **argv);

/*
** process_flags.c
*/

int								process_flag_log(t_corewar *cw, int argc,
													char **argv, int *i);
int								process_flag_n(t_corewar *cw, int argc,
		char **argv, int *i);
int								process_flag_dump(t_corewar *cw, int argc,
		char **argv, int *i);

/*
** process_file.c
*/

int								process_file(t_corewar *cw, char *filename);

/*
** print_1.c
*/

int								print_error(char *str, t_corewar *cw);
int								print_error_file(char *str, t_corewar *cw);
int								print_error_file_unknown_inst(
		unsigned char byte, t_corewar *cw);
int								print_error_file_inst(char *inst, char *str,
		t_corewar *cw);
void							print_now_cycle(t_corewar *cw);

/*
** print_utils.c
*/

void							print_utils_error(t_corewar *cw,
		char clear_color);
void							print_utils_file(t_corewar *cw,
		char clear_color);
void							print_col_str(t_corewar *cw, char *str,
		t_ccolor col);
void							print_col_nbr(t_corewar *cw, int nbr,
		t_ccolor col);

/*
** utils.c
*/

int								accurate_read(int fd, char *buffer,
		int n_bytes);
int								end_with(char *str, char *end);
void							revert_bytes(void *addr, int size);
int								regnumber_contains(int reg_n);

/*
** check_1.c, check_2.c, check_3.c
*/

int								check_magic_header(int fd, t_corewar *cw,
		t_player *pl);
int								check_name(int fd, t_corewar *cw,
		t_player *pl);
int								check_null(int fd, t_corewar *cw,
		t_player *pl);
int								check_code_size(int fd, t_corewar *cw,
		t_player *pl);
int								check_comment(int fd, t_corewar *cw,
		t_player *pl);

void							get_types(char types[3], char from);
int								get_size(t_instruction *inst, char type);
int								check_arg(char permission, char current);
int								check_instruction(t_corewar *cw, t_player *pl,
		t_instruction *inst, int i);

int								check_exe(int fd, t_corewar *cw,
		t_player *pl);
int								check_eof(int fd, t_corewar *cw,
		t_player *pl);

/*
** load_instructions.c
*/

void							load_instructions(t_corewar *cw);

/*
** load_instructions_utils.c
*/

void							set_instruction_base(t_instruction *inst,
		unsigned char byte, char *name, char type_byte);
void							set_instruction_args(t_instruction *inst,
		char arg1, char arg2, char arg3);
void							set_instruction_other(t_instruction *inst,
		int dir_size, int sleep,
		int (*f)(t_corewar*, t_carriage*));

/*
** insts.c
*/

t_instruction					*insts_find(t_corewar *cw, unsigned char byte);

/*
** preparations.c
*/

int								check_players(t_corewar *cw);
int								prepare_for_battle(t_corewar *cw);
void							show_players(t_corewar *cw);

/*
** carriage.c
*/

int								carriage_new(t_corewar *cw,
		unsigned char owner_id, int pos);
void							carriage_grab_instruction(t_corewar *cw,
		t_carriage *carr);
void							carriage_move(t_carriage *carr, int move);
int								carriage_copy(t_corewar *cw, t_carriage *carr,
		int pos);
void							carriage_move_by_types(t_corewar *cw,
		t_carriage *carr);

/*
** print_carriage.c
*/

void							print_bytes(t_corewar *cw, int pos, int count);
void							print_pc_movements(t_corewar *cw,
		t_carriage *carr);

/*
** corewar_play.c
*/

int								corewar_play(t_corewar *cw);

/*
** map.c
*/

int								map_normilize(int pos);
void							map_get(t_corewar *cw, int size, int pos,
		void *output);
void							map_set(t_corewar *cw, int size, int pos,
		void *input);
void							map_set_color(t_corewar *cw, int pos, int size,
		unsigned char owner_id);

/*
** instruction_functions_1.c, instruction_functions_2.c,
** instruction_functions_3.c, instruction_functions_4.c
*/

int								live_function(t_corewar *cw,
		t_carriage *carr);
int								ld_function(t_corewar *cw,
		t_carriage *carr);
int								st_function(t_corewar *cw,
		t_carriage *carr);

int								add_function(t_corewar *cw,
		t_carriage *carr);
int								sub_function(t_corewar *cw,
		t_carriage *carr);
int								and_function(t_corewar *cw,
		t_carriage *carr);
int								or_function(t_corewar *cw,
		t_carriage *carr);
int								xor_function(t_corewar *cw,
		t_carriage *carr);

int								zjmp_function(t_corewar *cw,
		t_carriage *carr);
int								ldi_function(t_corewar *cw,
		t_carriage *carr);
int								sti_function(t_corewar *cw,
		t_carriage *carr);
int								fork_function(t_corewar *cw,
		t_carriage *carr);
int								lld_function(t_corewar *cw,
		t_carriage *carr);

int								lldi_function(t_corewar *cw,
		t_carriage *carr);
int								lfork_function(t_corewar *cw,
		t_carriage *carr);
int								aff_function(t_corewar *cw,
		t_carriage *carr);

/*
** function_utils.c
*/

void							load_types(t_corewar *cw, t_carriage *carr);
int								check_types(t_corewar *cw, t_carriage *carr);
int								check_registers(t_corewar *cw,
		t_carriage *carr);

/*
** load_value_1.c, load_value_2.c
*/

void							load_ind_link(t_corewar *cw, t_carriage *carr,
		int arg_n);
void							load_ind(t_corewar *cw, t_carriage *carr,
		int arg_n, char idx);
void							load_dir(t_corewar *cw, t_carriage *carr,
		int arg_n);
void							load_value(t_corewar *cw, t_carriage *carr,
		int arg_n, char val_type);

void							load_reg_link(t_corewar *cw, t_carriage *carr,
		int arg_n);
void							load_reg(t_corewar *cw, t_carriage *carr,
		int arg_n);

/*
** dump.c
*/

int								corewar_dump(t_corewar *cw);

/*
** print_dump.c
*/

int								print_address(t_corewar *cw, int address);
void							print_map_byte(t_corewar *cw, int pos);

/*
** catsing_uc_hex.c
*/

char							*casting_uc_hex(int num, int width);

/*
** print_log.c, print_log_2.c
*/

void							print_log(t_corewar *cw, t_carriage *carr);

void							print_reg(t_corewar *cw, t_carriage *carr,
		int *i, int j);

/*
** print_log_functions.c
*/

void							print_log_zjmp(t_corewar *cw,
		t_carriage *carr);
void							print_log_ldi(t_corewar *cw,
		t_carriage *carr);
void							print_log_sti(t_corewar *cw,
		t_carriage *carr);
void							print_log_fork(t_corewar *cw,
		t_carriage *carr);
void							print_log_lfork(t_corewar *cw,
		t_carriage *carr);

/*
** kill_machine.c
*/

int								kill_machine(t_corewar *cw);

/*
** print_kill_machine.c
*/

void							print_carriage_death(t_corewar *cw,
		t_carriage *carr);
void							print_die_step(t_corewar *cw);
void							print_winner(t_corewar *cw, int id);

/*
** vis_sdl_help_1.c
*/

int								ft_init_sdl(t_corewar *cw);
int								init_sdl(t_corewar *cw);
void							ft_quit(t_corewar *cw);
void							ft_init_borders(t_corewar *cw);
int								ttf_print_str(t_corewar *cw, SDL_Color clr,
		SDL_Rect *dest, char *str);

/*
** vis_sdl_help_2.c
*/

void							ft_change_dst(SDL_Rect *dest, int delta_x,
		int delta_y);
void							ft_set_clr(SDL_Color *clr, int num);
void							ft_add_param(t_corewar *cw, SDL_Color *clr,
		SDL_Rect *dest, int num);
void							ft_event_procedure(t_corewar *cw);
int							ttf_print_str_free(t_corewar *cw, SDL_Color clr,
		SDL_Rect *dest, char *str);

/*
** vis_sdl_draw.c
*/

void							ft_vis_redraw(t_corewar *cw);
void							ttf_print_frames(t_corewar *cw);
void							ttf_print_fields(t_corewar *cw);
void							ttf_print_carrs(t_corewar *cw);
int								ft_count_carrs(t_carriage *carrs);

/*
** vis_sdl_ttf_1.c
*/

void							ttf_print_system(t_corewar *cw, int x_pos,
		int y_pos);
void							ttf_print_info(t_corewar *cw, int x_pos,
		int y_pos);
void							ttf_print_players_1_2(t_corewar *cw, int x_pos,
		int y_pos);
void							ttf_print_players_3_4(t_corewar *cw, int y_pos,
		int *i);
void							ttf_print_sep_player(t_corewar *cw,
		SDL_Color clr, SDL_Rect dest, int i);

/*
** vis_sdl_ttf_2.c
*/

void							ttf_print_label(t_corewar *cw);
void							ttf_arena_ds(t_corewar *cw, int x_pos);
void							ft_count_fields(t_corewar *cw, int *p);
void							ft_draw_arena_fields(t_corewar *cw,
		SDL_Rect dest, int p[], int del);
void							ttf_print_winner(t_corewar *cw, int x_pos,
		int y_pos);

#endif
