# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhealitt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 11:14:51 by rhealitt          #+#    #+#              #
#    Updated: 2019/08/21 12:01:55 by rhealitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = asm

NAME2 = corewar

NAME3 = disasm

LIBFT_DIR  = common/libft/

all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1):
	@$(MAKE) -C assembler/
	@mv assembler/asm ./asm

$(NAME2):
	@$(MAKE) -C vm/
	@mv vm/corewar ./corewar

$(NAME3):
	@$(MAKE) -C disassembler/
	@mv disassembler/disasm ./disasm

clean: $(NAME1)_clean $(NAME2)_clean $(NAME3)_clean

$(NAME1)_clean:
	@$(MAKE) -C Assembler/ clean

$(NAME2)_clean:
	@$(MAKE) -C VM/ clean

$(NAME3)_clean:
	@$(MAKE) -C Disassembler/ clean

fclean: $(NAME1)_fclean $(NAME2)_fclean $(NAME3)_fclean

$(NAME1)_fclean: $(NAME1)_clean
	@rm -f asm

$(NAME2)_fclean: $(NAME2)_clean
	@rm -f corewar

$(NAME3)_fclean: $(NAME3)_clean
	@rm -f disasm

re: $(NAME1)_fclean $(NAME2)_fclean $(NAME3)_fclean $(NAME1) $(NAME2) $(NAME3)