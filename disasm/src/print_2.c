/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:51:57 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/14 10:51:59 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void	print_comment(char *str, char options)
{
	print_col_str(options & DISASM_OPT_FILE_FORMAT ? ".comment " : "Comment: ",
		options, DISASM_COL_NAME);
	if (options & DISASM_OPT_FILE_FORMAT)
		ft_putchar('"');
	ft_putstr(str);
	if (options & DISASM_OPT_FILE_FORMAT)
		ft_putchar('"');
	ft_putchar('\n');
}

int		print_error_unknown_inst(unsigned char byte, char options)
{
	char		*str;
	static char	alpha[] = "0123456789abcdef";

	if ((str = ft_strdup("Unknown instruction **")) == NULL)
		return (print_error("DISASM Memory Error", options));
	str[20] = alpha[byte / 16];
	str[21] = alpha[byte % 16];
	print_error(str, options);
	free(str);
	return (0);
}

int		print_error_inst(char *inst, char *str, char options)
{
	int		inst_len;
	int		str_len;
	char	*str1;

	inst_len = ft_strlen(inst);
	str_len = ft_strlen(str);
	if ((str1 = ft_strnew(inst_len + str_len + 2)) == NULL)
		return (print_error("DISASM Memory Error", options));
	ft_memcpy(str1, inst, inst_len);
	ft_memcpy(str1 + inst_len + 2, str, str_len);
	str1[inst_len] = ':';
	str1[inst_len + 1] = ' ';
	print_error(str1, options);
	free(str1);
	return (0);
}
