#include "disasm.h"

void	print_comment(char *str, char colored)
{
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_NAME);
	ft_putstr("Comment: ");
	if (colored)
		ft_setcolor(cc_current, cc_default);
	ft_putstr(str);
	ft_putchar('\n');
}

int		print_error_unknown_inst(unsigned char byte, char colored)
{
	char	*str;
	char	alpha[] = "0123456789abcdef";

	if ((str = ft_strdup("Unknown instruction **")) == NULL)
		return (print_error("DISASM Memory Error", colored));
	str[20] = alpha[byte / 16];
	str[21] = alpha[byte % 16];
	print_error(str, colored);
	free(str);
	return (0);
}

int		print_error_inst(char *inst, char *str, char colored)
{
	int		inst_len;
	int		str_len;
	char	*str1;

	inst_len = ft_strlen(inst);
	str_len = ft_strlen(str);
	str1 = ft_strnew(inst_len + str_len + 2);
	ft_memcpy(str1, inst, inst_len);
	ft_memcpy(str1 + inst_len + 2, str, str_len);
	str1[inst_len] = ':';
	str1[inst_len + 1] = ' ';
	print_error(str1, colored);
	free(str1);
	return (0);
}
