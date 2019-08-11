/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:22:04 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/11 15:51:52 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		init_sdl(t_corewar *cw)
{
	cw->win = NULL;
	cw->ren = NULL;
	cw->fnt = NULL;
	cw->scr_w = -1;
	cw->scr_h = -1;
	cw->col = -1;
	cw->xl = -1;
	cw->xr = -1;
	cw->yu = -1;
	cw->yd = -1;
	return (ft_init_sdl(cw));
}

int		ft_init_sdl(t_corewar *cw)
{
	SDL_DisplayMode	dm;
	int				ok;

	ok = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ok = 1;
	else if (TTF_Init() != 0)
		ok = 2;
	else if (!(cw->win = SDL_CreateWindow("Core_War", SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, 0, 0,
						SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP)))
		ok = 3;
	else if (!(cw->ren = SDL_CreateRenderer(cw->win, -1, 0)))
		ok = 4;
	else if (!(cw->fnt = TTF_OpenFont(COURIER_TTF, 30)))
		ok = 5;
	else
	{
		SDL_GetCurrentDisplayMode(0, &dm);
		cw->scr_h = dm.h;
		cw->scr_w = dm.w;
		cw->scr_h == -1 || cw->scr_w == -1 ? ok = 6 : 0;
	}
	return (ok);
}

void	ft_quit(t_corewar *cw)
{
	SDL_DestroyWindow(cw->win);
	cw->win = NULL;
	SDL_DestroyRenderer(cw->ren);
	cw->ren = NULL;
	TTF_CloseFont(cw->fnt);
	TTF_Quit();
	SDL_Quit();
}
