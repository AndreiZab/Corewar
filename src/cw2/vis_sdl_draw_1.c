/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_draw_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:54:05 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/11 15:56:17 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_vis_redraw(t_corewar *cw)
{
	SDL_Event	e;

	ft_frames(cw);
	ft_fields(cw);
	ft_label(cw);
	ttf_print(cw, 10, 10);
	SDL_RenderPresent(cw->ren);
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
		{
			while (SDL_PollEvent(&e) != 0 || 1)
			{
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
					break ;
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
					ft_quit(cw);
			}
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			ft_quit(cw);
	}
}

void	ft_frames(t_corewar *cw)
{
	SDL_Rect	rect;
	int			i;

	SDL_SetRenderDrawColor(cw->ren, 0, 0, 0, 0);
	SDL_RenderClear(cw->ren);
	SDL_SetRenderDrawColor(cw->ren, 255, 255, 255, 0);
	i = 0;
	rect.x = 0;
	rect.y = 0;
	while (i < 11)
	{
		rect.w = cw->scr_w - rect.x * 2;
		rect.h = cw->scr_h - rect.y * 2;
		SDL_RenderDrawRect(cw->ren, &rect);
		rect.x += 2;
		rect.y += 2;
		i += 2;
	}
	SDL_RenderDrawLine(cw->ren, cw->scr_h - 5, 10,
								cw->scr_h - 5, cw->scr_h - 10 - 1);
	SDL_RenderDrawLine(cw->ren, cw->scr_h - 10, 10,
								cw->scr_h - 10, cw->scr_h - 10 - 1);
	cw->xl = cw->scr_h - 5;
	cw->xr = cw->scr_w - 10 - 2;
	cw->yu = 10;
	cw->yd = cw->scr_h - 10 - 1;
}

void	ft_label(t_corewar *cw)
{
	SDL_Surface	*tmp_surf;
	SDL_Texture	*tex;
	SDL_Color	clr;
	SDL_Rect	dest;

	clr.a = 0;
	clr.b = 250;
	clr.g = 250;
	clr.r = 250;
	tmp_surf = TTF_RenderText_Blended(cw->fnt, "CORE WAR - CORE WAR - CORE WAR - CORE WAR", clr);
	tex = SDL_CreateTextureFromSurface(cw->ren, tmp_surf);
	dest.x = cw->xl + ((cw->xr - cw->xl - tmp_surf->w) / 2);
	dest.y = cw->yd - tmp_surf->h;
	dest.w = tmp_surf->w;
	dest.h = tmp_surf->h;
	SDL_RenderCopy(cw->ren, tex, NULL, &dest);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(tmp_surf);
	SDL_SetRenderDrawColor(cw->ren, 255, 255, 255, 0);
	SDL_RenderDrawLine(cw->ren, cw->xl, dest.y - 15, cw->xr, dest.y - 15);
	SDL_RenderDrawLine(cw->ren, cw->xl, dest.y - 10, cw->xr, dest.y - 10);
}

void	ft_fields(t_corewar *cw)
{
	SDL_Rect	rect;
	int			i;

	i = -1;
	rect.h = (cw->scr_h - 128) / 64;
	rect.w = rect.h;
	SDL_SetRenderDrawColor(cw->ren, 170, 255, 187, 0);
	while (++i < MEM_SIZE)
	{
		rect.x = (i % 64) * rect.w + 2 * (i % 64) + 17;
		rect.y = (i / 64) * rect.h + 2 * (i / 64) + 17;
		SDL_RenderFillRect(cw->ren, &rect);
	}
}