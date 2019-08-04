#include "disasm.h"

void	print_filename(char *filename, char colored)
{
	ft_putstr("=====> ");
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_FILENAME);
	ft_putstr(filename);
	if (colored)
		ft_setcolor(cc_current, cc_default);
	ft_putstr(" <=====\n");
}

int		print_error(char *str, char colored)
{
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_ERROR);
	ft_putstr("Error: ");
	if (colored)
		ft_setcolor(cc_current, cc_default);
	ft_putstr(str);
	ft_putchar('\n');
	return (0);
}

void	print_name(char *str, char colored)
{
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_NAME);
	ft_putstr("Name: ");
	if (colored)
		ft_setcolor(cc_current, cc_default);
	ft_putstr(str);
	ft_putchar('\n');
}

void	print_code_size(int nbr, char colored)
{
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_NAME);
	ft_putstr("Code size: ");
	if (colored)
		ft_setcolor(cc_current, cc_default);
	ft_putnbr(nbr);
	ft_putchar('\n');
}

void	print_warning(char *str, char colored)
{
	if (colored)
		ft_setcolor(cc_current, DISASM_COL_WARNING);
	ft_putstr("Warning: ");
	if (colored)
		ft_setcolor(cc_current, cc_default);
	ft_putstr(str);
	ft_putchar('\n');
}
