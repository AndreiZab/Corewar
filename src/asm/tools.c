/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:24:06 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 19:14:23 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void		ft_revert_tokens(void)
{
	t_token *curr;
	t_token *prev;

	prev = NULL;
	if (g_data && g_data->tokens)
	{
		while (g_data->tokens)
		{
			curr = g_data->tokens->next;
			g_data->tokens->next = prev;
			g_data->tokens->prev = curr;
			prev = g_data->tokens;
			g_data->tokens = curr;
		}
		if (prev)
			g_data->tokens = prev;
	}
}

static void	ft_free_label_and_token(void)
{
	t_label *temp_l;
	t_token *temp_t;

	while (g_data->labels)
	{
		temp_l = g_data->labels->prev;
		free(g_data->labels);
		g_data->labels = temp_l;
	}
	while (g_data->tokens)
	{
		temp_t = g_data->tokens->next;
		if (g_data->tokens->content)
			free(g_data->tokens->content);
		free(g_data->tokens);
		g_data->tokens = temp_t;
	}
}

void		ft_free_data(void)
{
	if (g_data->name)
		free(g_data->name);
	if (g_data->comment)
		free(g_data->comment);
	if (g_data->labels || g_data->tokens)
		ft_free_label_and_token();
	if (g_data->output)
		free(g_data->output);
	free(g_data);
}

void		ft_create(int fd, char *str)
{
	t_data *data;

	g_data = 0;
	g_bytes = 0;
	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		ft_error("NO_MEMORY");
	data->fd = fd;
	data->filename = str;
	g_data = data;
}

void		ft_token_create(t_type type)
{
	t_token	*token;

	if (!(token = (t_token*)ft_memalloc(sizeof(t_token))))
		ft_error("NO_MEMORY");
	token->x = g_data->x;
	token->y = g_data->y;
	token->type = type;
	if (g_data->tokens)
		g_data->tokens->prev = token;
	token->next = g_data->tokens;
	g_data->tokens = token;
}
