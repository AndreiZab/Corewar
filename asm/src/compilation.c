 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compilation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:28:01 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 19:11:48 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static int32_t	ft_label(u_int32_t bytes, t_token *token)
{
	int32_t	move;
	t_label	*label;

	label = g_data->labels;
	while (label)
	{
		if (!(ft_strcmp(token->content, label->ptr->content)))
			break ;
		label = label->prev;
	}
	if (!label || !label->ptr)
		ft_error("INVALID_LABEL");
	move = label->ptr->bytes - bytes;
	return (move);
}

static void		arg_types_code(t_token *com, u_int32_t *carr, u_int8_t n_arg)
{
	int8_t	tmp;
	int		arg;

	tmp = 0;
	arg = 0;
	while (arg < n_arg)
	{
		if (com->type == Register)
			tmp |= 1 << 2 * (3 - arg++);
		else if (com->type == Direct || com->type == Direct_label)
			tmp |= 2 << 2 * (3 - arg++);
		else if (com->type == Indirect || com->type == Indirect_label)
			tmp |= 3 << 2 * (3 - arg++);
		com = com->next;
	}
	ft_itoh(tmp, 1, carr);
}

static void		ft_command_in_buf(t_token **com, u_int32_t *carr, u_int8_t type)
{
	u_int8_t n_arg;
	u_int8_t d_size;

	ft_itoh(g_op_tab[type].code, 1, carr);
	n_arg = g_op_tab[type].args_num;
	if (g_op_tab[type].args_types_code)
		arg_types_code(*com, carr, n_arg);
	*com = (*com)->next;
	while (n_arg--)
	{
		while ((*com)->type == Separator)
			*com = (*com)->next;
		d_size = g_op_tab[type].t_dir_size;
		if ((*com)->type == Register)
			ft_itoh(ft_atoi_cor((*com)->content + 1, 1), 1, carr);
		else if ((*com)->type == Direct)
			ft_itoh(ft_atoi_cor((*com)->content, d_size), d_size, carr);
		else if ((*com)->type == Indirect)
			ft_itoh(ft_atoi_cor((*com)->content, IND_SIZE), IND_SIZE, carr);
		else if ((*com)->type == Direct_label)
			ft_itoh(ft_label((*com)->bytes, *com), d_size, carr);
		else if ((*com)->type == Indirect_label)
			ft_itoh(ft_label((*com)->bytes, *com), IND_SIZE, carr);
		*com = (*com)->next;
	}
}

void			ft_compilation_champ(void)
{
	t_token		*token;
	u_int32_t	carriage;

	token = g_data->tokens;
	if (!(g_data->output = (char*)ft_memalloc(sizeof(char) * (2192 + g_bytes))))
		ft_error("NO_MEMORY");
	carriage = 0;
	ft_itoh(COREWAR_EXEC_MAGIC, 4, &carriage);
	carriage = 4 + PROG_NAME_LENGTH + 4;
	ft_itoh(g_bytes, 4, &carriage);
	carriage = 2192;
	ft_memcpy(g_data->output + 4 + PROG_NAME_LENGTH + 4 * 2,
			g_data->comment, ft_strlen(g_data->comment));
	ft_memcpy(g_data->output + 4, g_data->name, ft_strlen(g_data->name));
	while (token)
	{
		if (token->type == Instruction)
			ft_command_in_buf(&token, &carriage, token->bytes);
		token = token->next;
	}
}
