NAME=corewar

SRCS=main.c\
	print_1.c \
	print_utils.c \
	corewar_memory.c \
	load_instructions.c \
	load_instructions_utils.c \
	process_arguments.c \
	process_flags.c \
	process_file.c \
	utils.c \
	insts.c \
	check_1.c \
	check_2.c \
	check_3.c \
	preparations.c \
	carriage.c \
	print_carriage.c \
	corewar_play.c \
	map.c \
	instruction_functions_1.c \
	instruction_functions_2.c \
	instruction_functions_3.c \
	instruction_functions_4.c \
	function_utils.c \
	load_value_1.c \
	load_value_2.c \
	dump.c \
	print_dump.c \
	casting_uc_hex.c \
	print_log.c \
	print_log_2.c \
	print_log_functions.c \
	kill_machine.c \
	print_kill_machine.c \
	vis_sdl_help_1.c \
	vis_sdl_help_2.c \
	vis_sdl_draw.c \
	vis_sdl_ttf_1.c  \
	vis_sdl_ttf_2.c

SRCS_DIR=src
OBJS_DIR=obj

SDL_LIBS=`sdl2-config --libs` -lSDL2_ttf



INCLUDE=-I ../common/ -I include -I ../common/libft \
		`sdl2-config --cflags`
LIBFT_DIR=../common/libft

CFLAGS=-Wall -Wextra -Werror

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS_DIR) $(addprefix $(OBJS_DIR)/, $(OBJS))
	@printf "%-72c\rCreating corewar... " ' '
	@gcc $(CFLAGS) -o $(NAME) $(INCLUDE) $(addprefix $(OBJS_DIR)/, $(OBJS)) -L $(LIBFT_DIR) -lft $(SDL_LIBS)
	@printf "Done!\n"

$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@gcc $(CFLAGS) -o $@ $(INCLUDE) -c $<
	@printf "Compiling %29s => %-29s\r" $< $@

clean:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) fclean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
