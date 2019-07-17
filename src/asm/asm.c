/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:54:16 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/17 14:46:46 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void	ft_error(char *str, t_data *data)
{
	if (data && data->num_current_row)
	{
		ft_putstr_fd("line:", 2);
		ft_putnbr_fd(data->num_current_row, 2);
		ft_putchar_fd(' ', 2);
	}
	ft_putendl_fd(str, 2);
	exit(1);
}

int 	ft_check_name(char *str)
{
	int l;

	l = strlen(str);
	if (l > 2 && str[l] == '\0' && str[l - 1] == 's' && str[l - 2] == '.')
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	int err;

	if (argc == 2 && (err = ft_check_name(*(argv + 1))) == 1)
	{
		ft_asm(*(argv + 1));
		return (0);
	}
	else if (argc > 2)
		write(2, "TOO_MANY_FILES\n", 15);
	else if (argc < 2)
		write(2, "NO_INPUT_FILE\n", 14);
	else if (err)
		write(2, "WRONG_FILE_TYPE,_NEED_.s_FILE\n", 29);
	write(2, "Usage: ./asm champ.s\n", 21);
	return(0);
}