# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhealitt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/14 21:09:16 by rhealitt          #+#    #+#              #
#    Updated: 2019/07/14 21:20:29 by rhealitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =  asm

LIBF = lib/libft/

SRCS = src/asm/*.c

CCFL = -Wall -Wextra

all: $(NAME)

$(NAME):
	@make -C $(LIBF) re
	@gcc $(CCFL) -I ./include/asm/ -L $(LIBF) $(SRCS) -I $(LIBF) -I ./include/ -o $(NAME) -lft

clean:
	@make -C $(LIBF) clean

fclean: clean
	@make -C $(LIBF) fclean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re