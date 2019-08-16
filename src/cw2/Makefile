NAME=corewar

SRCS=main.c\
	print_1.c \
	print_utils.c \
	corewar_memory.c \
	load_instructions.c \
	load_instructions_utils.c \
	insts.c \
	process_arguments.c \
	process_flags.c \
	process_file.c \
	utils.c \
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
	print_kill_machine.c
SRCS_DIR=.
OBJS_DIR=obj

INCLUDE=-I ../../include/ -I ../../include/cw2 -I ../../lib/libft
LIBFT_DIR=../../lib/libft

CFLAGS=-Wall -Wextra -Werror

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS_DIR) $(addprefix $(OBJS_DIR)/, $(OBJS))
	@printf "%-72c\rCreating corewar... " ' '
	@gcc $(CFLAGS) -o $(NAME) $(INCLUDE) $(addprefix $(OBJS_DIR)/, $(OBJS)) -L $(LIBFT_DIR) -lft
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