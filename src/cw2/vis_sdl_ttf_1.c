/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_sdl_ttf_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 16:01:39 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/08/12 17:24:58 by qclubfoo         ###   ########.fr       */
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
	ttf_print_str(cw, clr, &dest, ft_itoa(ft_count_carrs(cw->carrs))); // верность указания переменной cw->carrs как total process;
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
	ft_change_dst(&dest, x_pos, y_pos);
	ttf_print_str(cw, clr, &dest, "<<ESC>> for exit");
	ft_change_dst(&dest, 0, cw->fnt_h * 2);
	ttf_print_str(cw, clr, &dest, "<<P>> for pause");
}
	// ft_change_dst(&dest, (cw->xr - cw->xl) / 2, 0);
	// ttf_print_str(cw, clr, &dest, "<<ESC>> for exit", 0);
	// ft_change_dst(&dest, 0, fnt_h * 2);
	// ttf_print_str(cw, clr, &dest, "<<P>> for pause", 0);
	// ft_change_dst(&dest, -(cw->xr - cw->xl) / 2, 0);
	// ft_change_dst(&dest, 0, fnt_h * 4);
	// ft_set_clr(&clr, 1);
	// if (cw->players_count >= 1)
	// {
	// 	ttf_player(cw, clr, dest, "Player ");
	// 	ft_change_dst(&dest, (cw->xr - cw->xl) / 2, 0);
	// 	ft_set_clr(&clr, 2);
	// }
	// if (cw->players_count >= 2)
	// {
	// 	ttf_player(cw, clr, dest, "Player ");
	// 	ft_change_dst(&dest, 0, fnt_h * 2 * 6);
	// 	ft_set_clr(&clr, 4);
	// }
	// if (cw->players_count >= 4)
	// {
	// 	ttf_player(cw, clr, dest, "Player ");
	// 	ft_change_dst(&dest, -(cw->xr - cw->xl) / 2, 0);
	// 	ft_set_clr(&clr, 3);
	// }
	// if (cw->players_count >= 3)
	// {
	// 	ttf_player(cw, clr, dest, "Player ");
	// 	ft_change_dst(&dest, 0, fnt_h * 2 * 6);
	// }
	// clr.r = 255;
	// clr.g = 255;
	// clr.b = 255;
	// ttf_print_str(cw, clr, &dest, "Arena distribution:", 0);
	// ft_change_dst(&dest, 0, fnt_h * 2);
	// ft_arena(cw, clr, dest);
// }

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

void	ft_add_param(t_corewar *cw, SDL_Color *clr, SDL_Rect *dest, int num)
{
	ft_set_clr(clr, num);
	dest->x = cw->xl;
	dest->y = cw->yu;
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

void	ft_arena(t_corewar *cw, SDL_Color clr, SDL_Rect dest)
{
	int	i;
	int	p1;
	int p2;
	int p3;
	int p4;
	int	delta;
	SDL_Color cl; // remoove;

	cl = clr;  //remoove;
	i = 0;
	p1 = p2 = p3 = p4 = 0;
	delta = MEM_SIZE / (cw->xr - cw->xl - 104);
	while (i < MEM_SIZE)
	{
		if (cw->players_map[i] == 1)
			p1++;
		else if (cw->players_map[i] == 2)
			p2++;
		else if (cw->players_map[i] == 3)
			p3++;
		else if (cw->players_map[i] == 4)
			p4++;
		i++;
	}
	SDL_SetRenderDrawColor(cw->ren, GRY);
	dest.w = (cw->xr - cw->xl) - 100;
	dest.h = 30;
	SDL_RenderFillRect(cw->ren, &dest);
	dest.y += 2;
	dest.h -= 4;
	dest.w -= 4;
	dest.x += 2;
	SDL_SetRenderDrawColor(cw->ren, RD);
	dest.w = p1 / delta;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, GRN);
	dest.x += dest.w;
	dest.w = p2 / delta;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, BL);
	dest.x += dest.w;
	dest.w = p3 / delta;
	SDL_RenderFillRect(cw->ren, &dest);
	SDL_SetRenderDrawColor(cw->ren, YLW);
	dest.x += dest.w;
	dest.w = p4 / delta;
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

void	ft_change_dst(SDL_Rect *dest, int delta_x, int delta_y)
{
	dest->x += delta_x;
	dest->y += delta_y;
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