/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_ttf_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:54:05 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/19 12:10:58 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ttf_print_label(t_corewar *cw)
{
	SDL_Surface	*tmp_surf;
	SDL_Texture	*tex;
	SDL_Color	clr;
	SDL_Rect	dest;

	clr.a = 0;
	clr.b = 255;
	clr.g = 255;
	clr.r = 255;
	tmp_surf = TTF_RenderText_Blended(cw->fnt,
				"CORE WAR - CORE WAR - CORE WAR - CORE WAR - CORE WAR", clr);
	tex = SDL_CreateTextureFromSurface(cw->ren, tmp_surf);
	dest.x = cw->xl + ((cw->xr - cw->xl - tmp_surf->w) / 2);
	dest.y = cw->yd - tmp_surf->h;
	dest.w = tmp_surf->w;
	dest.h = tmp_surf->h;
	SDL_RenderCopy(cw->ren, tex, NULL, &dest);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(tmp_surf);
	SDL_SetRenderDrawColor(cw->ren, WHT);
	SDL_RenderDrawLine(cw->ren, cw->xl, dest.y - 10, cw->xr, dest.y - 10);
	SDL_RenderDrawLine(cw->ren, cw->xl, dest.y - 5, cw->xr, dest.y - 5);
}

void	ttf_arena_ds(t_corewar *cw, int x_pos)
{
	SDL_Rect	dest;
	SDL_Color	clr;
	int			p[4];
	int			del;

	ft_add_param(cw, &clr, &dest, WHT_COL);
	ft_change_dst(&dest, x_pos, (cw->yd - cw->yu) / 4 * 3);
	ttf_print_str(cw, clr, &dest, "Arena distribution:");
	ft_change_dst(&dest, 0, cw->fnt_h * 2);
	del = MEM_SIZE / (cw->xr - cw->xl - 104);
	ft_count_fields(cw, p);
	ft_draw_arena_fields(cw, dest, p, del);
}

void	ft_count_fields(t_corewar *cw, int *p)
{
	int	i;

	i = -1;
	while (++i < 4)
		p[i] = 0;
	while (i < MEM_SIZE)
	{
		if (cw->players_map[i] == 1)
			p[0] += 1;
		else if (cw->players_map[i] == 2)
			p[1] += 1;
		else if (cw->players_map[i] == 3)
			p[2] += 1;
		else if (cw->players_map[i] == 4)
			p[3] += 1;
		i++;
	}
}

void	ft_draw_arena_fields(t_corewar *cw, SDL_Rect dest, int p[], int del)
{
	SDL_SetRenderDrawColor(cw->ren, GRY);
	dest.w = (cw->xr - cw->xl) - 100;
	dest.h = 30;
	SDL_RenderFillRect(cw->ren, &dest);
	dest.y += 2;
	dest.h -= 4;
	dest.w -= 4;
	dest.x += 2;
	SDL_SetRenderDrawColor(cw->ren, RD);
	dest.w = p[0] / del;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, GRN);
	dest.x += dest.w;
	dest.w = p[1] / del;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, BL);
	dest.x += dest.w;
	dest.w = p[2] / del;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, YLW);
	dest.x += dest.w;
	dest.w = p[3] / del;
	SDL_RenderFillRect(cw->ren, &dest);
}

void	ttf_print_winner(t_corewar *cw, int x_pos, int y_pos)
{
	SDL_Color	clr;
	SDL_Rect	dest;

	ft_add_param(cw, &clr, &dest, WHT_COL);
	ft_change_dst(&dest, x_pos, y_pos - cw->fnt_h * 8);
	ttf_print_str(cw, clr, &dest, "WINNER IS ");
	ft_change_dst(&dest, 0, cw->fnt_h * 2);
	ttf_print_str(cw, clr, &dest, cw->winner->name);
}
