/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:50:20 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/17 11:57:42 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void	print_filename(char *filename, char options)
{
	ft_putstr("=====> ");
	print_col_str(filename, options, DISASM_COL_FILENAME);
	ft_putstr(" <=====\n");
}

int		print_error(char *str, char options)
{
	print_col_str("Error: ", options, DISASM_COL_ERROR);
	ft_putstr(str);
	ft_putchar('\n');
	return (0);
}

void	print_name(char *str, char options)
{
	print_col_str(options & DISASM_OPT_FILE_FORMAT ? ".name" : "Name: ",
		options, DISASM_COL_NAME);
	if (options & DISASM_OPT_FILE_FORMAT)
		ft_putchar('"');
	ft_putstr(str);
	if (options & DISASM_OPT_FILE_FORMAT)
		ft_putchar('"');
	ft_putchar('\n');
}

void	print_code_size(int nbr, char options)
{
	if (!(options & DISASM_OPT_FILE_FORMAT))
	{
		print_col_str("Code size: ", options, DISASM_COL_NAME);
		ft_putnbr(nbr);
		ft_putchar('\n');
	}
}

void	print_warning(char *str, char options)
{
	print_col_str("Warning: ", options, DISASM_COL_WARNING);
	ft_putstr(str);
	ft_putchar('\n');
}
