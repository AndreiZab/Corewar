#include "ft_cw.h"

/*
** RU
** Обработчики аргументов
*/

int ft_process_flag_pinfo(t_corewar *cw, int argc, char **argv, int *arg_i)
{
	cw->pinfo = 1;
	return (FT_OK);
}