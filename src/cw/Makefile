NAME=corewar
SRC=main.c\
	argh.c \
	arg_process_1.c \
	arg_process_2.c \
	players.c \
	carriage.c \
	accurate_reader.c \
	exe_reader.c \
	others.c \
	casting_uc_hex.c \
	dump.c \
	comm_process.c \
	carr_load.c \
	map_set.c \
	map_get.c \
	tick.c \
	commh.c \
	kill_machine.c \
	bandles.c \
	cw.c

OBJ=$(SRC:.c=.o)

LIBFT=../../lib/libft
INCLUDE=-I ../../include -I ../../include/cw -I $(LIBFT)
CFLAGS=-g3


all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDE) -L $(LIBFT) -lft

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.o: %.c
	@gcc $(CFLAGS) $(INCLUDE) -c $< -L $(LIBFT) -lft

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT) fclean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re