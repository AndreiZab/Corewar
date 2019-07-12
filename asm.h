/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:03:28 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/12 11:47:24 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ASM_H
# define ASM_H


# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "libft/libft.h"
# include "op.h"

typedef struct	s_data
{
	int		fd;
	int		num_current_row;
	char 	*name;
	char 	*comment;
	int		code_size;

}				t_data;

/*
** parse_asm.c
 */

void		ft_asm(char *str);

/*
** asm.c
 */

void		ft_error(char *str, t_data *data);

#endif
