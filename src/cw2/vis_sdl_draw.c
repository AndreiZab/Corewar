/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:54:05 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/16 16:37:52 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_vis_redraw(t_corewar *cw)
{
	SDL_Event	e;

	ttf_print_frames(cw);
	ttf_print_fields(cw);
	ttf_print_label(cw);
	ttf_print_system(cw, 20, 10);
	ttf_print_info(cw, 20, 10);
	ttf_print_players_1_2(cw, 20, 10);
	ttf_arena_ds(cw, 20);
	if (cw->winner)
		ttf_print_winner(cw, 20, cw->yd - cw->yu);
	SDL_RenderPresent(cw->ren);
	while (SDL_PollEvent(&e) != 0)
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
			ft_quit(cw);
	}
}

void	ttf_print_frames(t_corewar *cw)
{
	SDL_Rect	rect;
	int			i;

	SDL_SetRenderDrawColor(cw->ren, BLK);
	SDL_RenderClear(cw->ren);
	SDL_SetRenderDrawColor(cw->ren, WHT);
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
}

void	ttf_print_fields(t_corewar *cw)
{
	SDL_Rect	rect;
	int			i;

	i = -1;
	rect.h = (cw->scr_h - 128) / 64;
	rect.w = rect.h;
	while (++i < MEM_SIZE)
	{
		if (cw->players_map[i] == 1)
			SDL_SetRenderDrawColor(cw->ren, RD);
		else if (cw->players_map[i] == 2)
			SDL_SetRenderDrawColor(cw->ren, GRN);
		else if (cw->players_map[i] == 3)
			SDL_SetRenderDrawColor(cw->ren, BL);
		else if (cw->players_map[i] == 4)
			SDL_SetRenderDrawColor(cw->ren, YLW);
		else
			SDL_SetRenderDrawColor(cw->ren, GRY);
		rect.x = (i % 64) * rect.w + 2 * (i % 64) + 17;
		rect.y = (i / 64) * rect.h + 2 * (i / 64) + 17;
		SDL_RenderFillRect(cw->ren, &rect);
	}
	ttf_print_carrs(cw);
}

void	ttf_print_carrs(t_corewar *cw)
{
	SDL_Rect	rect;
	t_carriage	*tmp;

	tmp = cw->carrs;
	rect.h = (cw->scr_h - 128) / 64 + 2;
	rect.w = rect.h;
	SDL_SetRenderDrawColor(cw->ren, WHT);
	while (tmp)
	{
		rect.x = (tmp->pc % 64) * rect.w + 16;
		rect.y = (tmp->pc / 64) * rect.h + 16;
		SDL_RenderDrawRect(cw->ren, &rect);
		rect.x = -1;
		rect.y = -1;
		tmp = tmp->next;
	}
	tmp = NULL;
}

int		ft_count_carrs(t_carriage *carrs)
{
	t_carriage	*tmp;
	int			i;

	i = 0;
	tmp = carrs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
