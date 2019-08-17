/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:41:08 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:41:10 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_log_zjmp(t_corewar *cw, t_carriage *carr)
{
	if (cw->log & COREWAR_OPT_LOG_ORIGINAL)
		print_col_str(cw, (carr->carry) ? " OK" : " FAILED",
			(carr->carry) ? cc_green : cc_red);
	else
		print_col_str(cw, (carr->carry) ? " Accepted" : " Denied",
			(carr->carry) ? cc_green : cc_red);
	ft_putchar('\n');
}

void	print_log_ldi(t_corewar *cw, t_carriage *carr)
{
	ft_putstr("\n       |");
	if (!(cw->log & COREWAR_OPT_LOG_ORIGINAL))
	{
		ft_putstr(" r");
		ft_putnbr(cw->args[0]);
	}
	ft_putstr(" -> load from ");
	ft_putnbr(cw->args[0]);
	ft_putstr(" + ");
	ft_putnbr(cw->args[1]);
	ft_putstr(" = ");
	ft_putnbr(cw->args[0] + cw->args[1]);
	ft_putstr(" (with pc and mod ");
	ft_putnbr(carr->pc_comm + (cw->args[0] + cw->args[1]) % IDX_MOD);
	ft_putstr(")\n");
}

void	print_log_sti(t_corewar *cw, t_carriage *carr)
{
	ft_putstr("\n       |");
	if (!(cw->log & COREWAR_OPT_LOG_ORIGINAL))
	{
		ft_putchar(' ');
		ft_putnbr(cw->args[0]);
	}
	ft_putstr(" -> store to ");
	ft_putnbr(cw->args[1]);
	ft_putstr(" + ");
	ft_putnbr(cw->args[2]);
	ft_putstr(" = ");
	ft_putnbr(cw->args[1] + cw->args[2]);
	ft_putstr(" (with pc and mod ");
	ft_putnbr(carr->pc_comm + (cw->args[1] + cw->args[2]) % IDX_MOD);
	ft_putstr(")\n");
}

void	print_log_fork(t_corewar *cw, t_carriage *carr)
{
	ft_putstr(" (");
	ft_putnbr(carr->pc_comm + (cw->args[0] % IDX_MOD));
	ft_putstr(")\n");
}

void	print_log_lfork(t_corewar *cw, t_carriage *carr)
{
	ft_putstr(" (");
	ft_putnbr(carr->pc_comm + cw->args[0]);
	ft_putstr(")\n");
}
