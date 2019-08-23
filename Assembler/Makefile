# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhealitt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/14 21:09:16 by rhealitt          #+#    #+#              #
#    Updated: 2019/08/19 11:47:31 by rhealitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  asm

LIBFT = ../common/libft/libft.a
LIBFT_DIR  = ../common/libft/
LIBRARIES = -L ../common/libft/

OP_H = -I ../common/
ASM_H = -I ./include/

HEAD = ./include/ft_asm.h
SRCS = asm.c \
	compilation.c \
	parse_asm.c \
	parse_asm_01.c \
	row_is_code.c \
	row_is_code_02.c \
	syntax_analysis.c \
	tools.c \
	write_bytes.c


OBJ_DIR = ./obj/
OBJECTS = $(patsubst %.c, %.o, $(SRCS))
OBJ	= $(addprefix ./obj/, $(OBJECTS))

CCFL = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@printf "%70c\rCreating asm... " ' '
	@$(CCFL) $(OP_H) $(LIBRARIES) $(OBJ) -I $(LIBFT_DIR) $(ASM_H) -o $(NAME) $(LIBFT)
	@printf "Done!\n"

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : ./src/%.c $(HEAD)
	@$(CC) -c  $(OP_H) $(ASM_H) -I $(LIBFT_DIR) $< -o $@
	@printf "Compiling... %27s => %-27s\r" $< $@

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
