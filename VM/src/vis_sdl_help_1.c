/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_help_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:22:04 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/19 12:10:58 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_init_sdl(t_corewar *cw)
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
	return (init_sdl(cw));
}

int		init_sdl(t_corewar *cw)
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
	ft_init_borders(cw);
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
	cw->options -= COREWAR_OPT_VISUALIZER;
}

void	ft_init_borders(t_corewar *cw)
{
	cw->xl = cw->scr_h - 5;
	cw->xr = cw->scr_w - 10 - 2;
	cw->yu = 10;
	cw->yd = cw->scr_h - 10 - 1;
}

int		ttf_print_str(t_corewar *cw, SDL_Color clr, SDL_Rect *dest, char *str)
{
	SDL_Surface	*tmp_surf;
	SDL_Texture	*tex;

	tmp_surf = TTF_RenderText_Blended(cw->fnt, str, clr);
	tex = SDL_CreateTextureFromSurface(cw->ren, tmp_surf);
	dest->w = tmp_surf->w;
	dest->h = tmp_surf->h;
	cw->fnt_h = tmp_surf->h;
	SDL_RenderCopy(cw->ren, tex, NULL, dest);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(tmp_surf);
	return (dest->w);
}
