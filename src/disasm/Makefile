NAME=disasm

SRCS=main.c\
	print_1.c \
	print_2.c \
	print_3.c \
	check_1.c \
	check_2.c \
	check_3.c \
	load_inst.c \
	utils.c
SRCS_DIR=.
OBJS_DIR=obj

INCLUDE=-I ../../include/ -I ../../include/disasm -I ../../lib/libft
LIBFT_DIR=../../lib/libft

CFLAGS=-Wall -Wextra -Werror

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS_DIR) $(addprefix $(OBJS_DIR)/, $(OBJS))
	@printf "%-60c\rCreating disasm... " ' '
	@gcc $(CFLAGS) -o $(NAME) $(INCLUDE) $(addprefix $(OBJS_DIR)/, $(OBJS)) -L $(LIBFT_DIR) -lft
	@printf "Done!\n"

$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@gcc -o $@ $(INCLUDE) -c $<
	@printf "Compiling %23s => %-23s\r" $< $@

clean:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) fclean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re