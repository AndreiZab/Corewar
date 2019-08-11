#include "corewar.h"

void	print_utils_error(t_corewar *cw, char clear_color)
{
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, COREWAR_COLOR_ERROR);
	ft_putstr("Error: ");
	if (clear_color && cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
}

void	print_utils_file(t_corewar *cw, char clear_color)
{
	if (cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, COREWAR_COLOR_FILENAME);
	ft_putstr("File '");
	ft_putstr(cw->current_filename);
	ft_putstr("': ");
	if (clear_color && cw->options & COREWAR_OPT_COLORS)
		ft_setcolor(cc_current, cc_default);
}