/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_help_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:22:04 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/19 14:32:06 by qclubfoo         ###   ########.fr       */
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

void	ft_event_procedure(t_corewar *cw)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e) != 0 || cw->winner)
	{
		if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p) || cw->winner)
		{
			while (SDL_PollEvent(&e) != 0 || 1)
			{
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
					break ;
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
					break ;
			}
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			break ;
	}
	if (e.key.keysym.sym == SDLK_ESCAPE)
		ft_quit(cw);
}

int		ttf_print_str_free(t_corewar *cw, SDL_Color clr, SDL_Rect *dest, char *str)
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
	free(str);
	str = NULL;
	return (dest->w);
}