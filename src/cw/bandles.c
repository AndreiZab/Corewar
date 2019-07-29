#include "ft_cw.h"

void	ft_bandle_args(t_corewar *cw)
{
	cw->argh = NULL;
	cw->argh_default = NULL;
	ft_argh_add(&(cw->argh), "-n", ft_process_flag_n); // Обработка флагов
	ft_argh_add(&(cw->argh), "-v", ft_process_flag_v);
	ft_argh_add(&(cw->argh), "-a", ft_process_flag_a);
	ft_argh_add(&(cw->argh), "-dump", ft_process_flag_dump);
	ft_argh_add(&(cw->argh), "-pinfo", ft_process_flag_pinfo);
	ft_argh_add(&(cw->argh_default), NULL, ft_process_file); // Обработка названий файлов
}

void	ft_bandle_commands(t_corewar *cw)
{
	cw->commh = NULL;
	cw->commh_default = NULL;
	ft_commh_add(&(cw->commh), 1, 10, ft_comm_live);
	ft_commh_add(&(cw->commh), 2, 5, ft_comm_ld);
	ft_commh_add(&(cw->commh), 3, 5, ft_comm_st);
	ft_commh_add(&(cw->commh), 4, 10, ft_comm_add);
	ft_commh_add(&(cw->commh), 5, 10, ft_comm_sub);
	ft_commh_add(&(cw->commh), 6, 6, ft_comm_and);
	ft_commh_add(&(cw->commh), 7, 6, ft_comm_or);
	ft_commh_add(&(cw->commh), 8, 6, ft_comm_xor);
	ft_commh_add(&(cw->commh), 9, 20, ft_comm_zjmp);
	ft_commh_add(&(cw->commh), 10, 25, ft_comm_ldi);
	ft_commh_add(&(cw->commh), 11, 25, ft_comm_sti);
	ft_commh_add(&(cw->commh), 12, 800, ft_comm_fork);
	ft_commh_add(&(cw->commh), 13, 10, ft_comm_lld);
	ft_commh_add(&(cw->commh), 14, 50, ft_comm_lldi);
	ft_commh_add(&(cw->commh), 15, 1000, ft_comm_lfork);
	(cw->aff) ? ft_commh_add(&(cw->commh), 16, 2, ft_comm_aff) : NULL;
	ft_commh_add(&(cw->commh_default), 0, 1, ft_comm_unknown);
}