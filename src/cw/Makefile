NAME=corewar
SRC=main.c\
	argh.c \
	arg_process.c \
	players.c \
	accurate_reader.c \
	exe_reader.c

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