/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_help_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:22:04 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/15 16:48:58 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_change_dst(SDL_Rect *dest, int delta_x, int delta_y)
{
	dest->x += delta_x;
	dest->y += delta_y;
}

void	ft_set_clr(SDL_Color *clr, int num)
{
	clr->a = 0;
	clr->r = 0;
	clr->g = 0;
	clr->b = 0;
	if (num == 0)
	{
		clr->r = 255;
		clr->g = 255;
		clr->b = 255;
	}
	else if (num == 1)
		clr->r = 170;
	else if (num == 2)
		clr->g = 170;
	else if (num == 3)
		clr->b = 250;
	else if (num == 4)
	{
		clr->r = 170;
		clr->g = 170;
	}
}

void	ft_add_param(t_corewar *cw, SDL_Color *clr, SDL_Rect *dest, int num)
{
	ft_set_clr(clr, num);
	dest->x = cw->xl;
	dest->y = cw->yu;
}
