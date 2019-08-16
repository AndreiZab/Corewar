/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_ttf_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 16:01:39 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/16 14:42:12 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ttf_print_system(t_corewar *cw, int x_pos, int y_pos)
{
	SDL_Color	clr;
	SDL_Rect	dest;
	int			x_dif;

	ft_add_param(cw, &clr, &dest, WHT_COL);
	ft_change_dst(&dest, x_pos, y_pos);
	x_dif = ttf_print_str(cw, clr, &dest, "total process: ");
	ft_change_dst(&dest, x_dif, 0);
	ttf_print_str(cw, clr, &dest, ft_itoa(ft_count_carrs(cw->carrs)));
	ft_change_dst(&dest, -x_dif, cw->fnt_h * 2);
	x_dif = ttf_print_str(cw, clr, &dest, "cycle: ");
	ft_change_dst(&dest, x_dif, 0);
	ttf_print_str(cw, clr, &dest, ft_itoa(cw->cycle));
	ft_change_dst(&dest, -x_dif, cw->fnt_h * 4);
	x_dif = ttf_print_str(cw, clr, &dest, "cycles to die: ");
	ft_change_dst(&dest, x_dif, 0);
	ttf_print_str(cw, clr, &dest, ft_itoa(cw->cycle_to_die));
	ft_change_dst(&dest, -x_dif, cw->fnt_h * 2);
	x_dif = ttf_print_str(cw, clr, &dest, "cycle delta: ");
	ft_change_dst(&dest, x_dif, 0);
	ttf_print_str(cw, clr, &dest, ft_itoa(cw->die_step));
}

void	ttf_print_info(t_corewar *cw, int x_pos, int y_pos)
{
	SDL_Color	clr;
	SDL_Rect	dest;

	ft_add_param(cw, &clr, &dest, WHT_COL);
	ft_change_dst(&dest, x_pos + (cw->xr - cw->xl) / 2, y_pos);
	ttf_print_str(cw, clr, &dest, "<<ESC>> for exit");
	ft_change_dst(&dest, 0, cw->fnt_h * 2);
	ttf_print_str(cw, clr, &dest, "<<P>> for pause");
}

void	ttf_print_players_1_2(t_corewar *cw, int x_pos, int y_pos)
{
	int			i;
	SDL_Color	clr;
	SDL_Rect	dest;

	i = 0;
	while (++i <= cw->players_count && i < 5)
	{
		if (i == 1)
		{
			ft_add_param(cw, &clr, &dest, RD_COL);
			ft_change_dst(&dest, x_pos, y_pos + (cw->yd - cw->yu) / 4);
			ttf_print_sep_player(cw, clr, dest, i - 1);
		}
		else if (i == 2)
		{
			ft_add_param(cw, &clr, &dest, GRN_COL);
			ft_change_dst(&dest, x_pos, y_pos + (cw->yd - cw->yu) / 2);
			ttf_print_sep_player(cw, clr, dest, i - 1);
		}
		else if (i > 2)
			ttf_print_players_3_4(cw, y_pos, &i);
	}
}

void	ttf_print_players_3_4(t_corewar *cw, int y_pos, int *i)
{
	SDL_Color	clr;
	SDL_Rect	dest;

	if (*i == 3)
	{
		ft_add_param(cw, &clr, &dest, BL_COL);
		ft_change_dst(&dest, (cw->xr - cw->xl) / 2,
										y_pos + (cw->yd - cw->yu) / 4);
		ttf_print_sep_player(cw, clr, dest, (*i) - 1);
	}
	else if (*i == 4)
	{
		ft_add_param(cw, &clr, &dest, YLW_COL);
		ft_change_dst(&dest, (cw->xr - cw->xl) / 2,
										y_pos + (cw->yd - cw->yu) / 2);
		ttf_print_sep_player(cw, clr, dest, (*i) - 1);
	}
}

void	ttf_print_sep_player(t_corewar *cw, SDL_Color clr, SDL_Rect dest, int i)
{
	int	x_dif;

	x_dif = ttf_print_str(cw, clr, &dest, "Player ");
	ft_change_dst(&dest, x_dif, 0);
	ttf_print_str(cw, clr, &dest, ft_itoa(i + 1));
	ft_change_dst(&dest, -x_dif, cw->fnt_h * 2);
	ttf_print_str(cw, clr, &dest, cw->players[i].name);
	ft_change_dst(&dest, 0, cw->fnt_h * 2);
	x_dif = ttf_print_str(cw, clr, &dest, "Last live: ");
	ft_change_dst(&dest, x_dif, 0);
	ttf_print_str(cw, clr, &dest, ft_itoa(cw->players[i].live));
}
