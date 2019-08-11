/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_ttf_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 16:01:39 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/11 16:41:37 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ttf_print(t_corewar *cw, int x_pos, int y_pos)
{
	SDL_Color	clr;
	SDL_Rect	dest;
	int			fnt_h;

	ft_add_param(cw, &clr, &dest);
	TTF_CloseFont(cw->fnt);
	cw->fnt = TTF_OpenFont(COURIER_TTF, 30);
	ft_change_dst(&dest, x_pos, y_pos);
	fnt_h = ttf_print_str(cw, clr, &dest, "total process: ");
	ft_change_dst(&dest, (cw->xr - cw->xl) / 2, 0);
	ttf_print_str(cw, clr, &dest, "<<ESC>> for exit");
	ft_change_dst(&dest, 0, fnt_h * 2);
	ttf_print_str(cw, clr, &dest, "<<P>> for pause");
	ft_change_dst(&dest, -(cw->xr - cw->xl) / 2, 0);
	ttf_print_str(cw, clr, &dest, "cycle: ");
	ft_change_dst(&dest, 0, fnt_h * 4);
	ttf_print_str(cw, clr, &dest, "cycles to die: ");
	ft_change_dst(&dest, 0, fnt_h * 2);
	ttf_print_str(cw, clr, &dest, "cycle delta: ");
	ft_change_dst(&dest, 0, fnt_h * 4);
	clr.r /= 2;
	ttf_player(cw, clr, dest, "Player 1");
	ft_change_dst(&dest, (cw->xr - cw->xl) / 2, 0);
	clr.g /= 2;
	ttf_player(cw, clr, dest, "Player 2");
	ft_change_dst(&dest, 0, fnt_h * 2 * 6);
	clr.b /= 2;
	ttf_player(cw, clr, dest, "Player 4");
	ft_change_dst(&dest, -(cw->xr - cw->xl) / 2, 0);
	clr.r = 0;
	ttf_player(cw, clr, dest, "Player 3");
	ft_change_dst(&dest, 0, fnt_h * 2 * 6);
	clr.r = 255;
	clr.g = 255;
	clr.b = 255;
	ttf_print_str(cw, clr, &dest, "Arena distribution:");
	ft_change_dst(&dest, 0, fnt_h * 2);
	ft_arena(cw, clr, dest);
}

void	ft_arena(t_corewar *cw, SDL_Color clr, SDL_Rect dest)
{
	SDL_Color cl; // remoove;

	cl = clr;  //remoove;
	SDL_SetRenderDrawColor(cw->ren, 255, 255, 255, 0);
	dest.w = (cw->xr - cw->xl) - 100;
	dest.h = 30;
	SDL_RenderFillRect(cw->ren, &dest);
	dest.y += 2;
	dest.h -= 4;
	dest.w -= 4;
	dest.x += 2;
	SDL_SetRenderDrawColor(cw->ren, 255, 0, 0, 0);
	dest.w /= 2;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, 0, 255, 0, 0);
	dest.x += dest.w;
	dest.w /= 2;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, 0, 0, 255, 0);
	dest.x += dest.w;
	dest.w /= 2;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, 0, 0, 255, 0);
	dest.x += dest.w;
	dest.w /= 2;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, 255, 0, 255, 0);
	dest.x += dest.w;
	dest.w /= 2;
	SDL_RenderFillRect(cw->ren, &dest);
}

void	ttf_player(t_corewar *cw, SDL_Color clr, SDL_Rect dest, char *str)
{
	ttf_print_str(cw, clr, &dest, str);
	ft_change_dst(&dest, 0, dest.h * 2);
	ttf_print_str(cw, clr, &dest, "Name");
	ft_change_dst(&dest, 0, dest.h * 2);
	ttf_print_str(cw, clr, &dest, "Last live: ");
	ft_change_dst(&dest, 0, dest.h * 2);
	ttf_print_str(cw, clr, &dest, "Lives in current period: ");
}

void	ft_add_param(t_corewar *cw, SDL_Color *clr, SDL_Rect *dest)
{
	clr->a = 0;
	clr->b = 250;
	clr->g = 250;
	clr->r = 250;
	dest->x = cw->xl;
	dest->y = cw->yu;
}

void	ft_change_dst(SDL_Rect *dest, int delta_x, int delta_y)
{
	dest->x += delta_x;
	dest->y += delta_y;
}

int		ttf_print_str(t_corewar *cw, SDL_Color clr, SDL_Rect *dest, char *str)
{
	SDL_Surface	*tmp_surf;
	SDL_Texture	*tex;
	int			fnt_h;

	tmp_surf = TTF_RenderText_Blended(cw->fnt, str, clr);
	tex = SDL_CreateTextureFromSurface(cw->ren, tmp_surf);
	dest->w = tmp_surf->w;
	dest->h = tmp_surf->h;
	fnt_h = tmp_surf->h;
	SDL_RenderCopy(cw->ren, tex, NULL, dest);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(tmp_surf);
	return (fnt_h);
}

// void	timer(int msec)
// {
// 	double	sec;
// 	time_t	start;
// 	time_t	end;
// 	double	elapsed;

// 	sec = (double)msec / 1000;
//     time(&start);
// 	time(&end);
//     elapsed = difftime(end, start);
//     while(elapsed < sec)
// 	{
// 		time(&end);
//     	elapsed = difftime(end, start);
// 	}
// }