NAME=corewar
SRC=main.c\
	args.c

OBJ=$(SRC:.c=.o)

LIBFT=../../lib/libft
INCLUDE=-I ../../include -I ../../include/cw -I $(LIBFT)


all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(INCLUDE) -L $(LIBFT) -lft

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.o: %.c
	@gcc $(INCLUDE) -c $< -L $(LIBFT) -lft