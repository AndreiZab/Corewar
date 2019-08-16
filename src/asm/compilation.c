/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compilation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:28:01 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 18:02:56 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void		ft_itoh(int32_t dec, int dir_size, u_int32_t *curr)
{
	int			step;
	int			start_size;

	start_size = dir_size;
	step = 0;
	while (dir_size)
	{
		g_data->output[*curr + dir_size - 1] = (u_int8_t)((dec >> step) & 0xFF);
		step += 8;
		dir_size--;
	}
	*curr += start_size;
}

int32_t		ft_atoi_cor(const char *str, u_int8_t size)
{
	int				sign;
	int				i;
	int64_t			nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ('0' <= str[i] && str[i] <= '9')
		nbr = nbr * 10 + ((int)str[i++] - '0');
	size == 1 ? (nbr = (u_int8_t)nbr) : 1;
	size == 2 ? (nbr = (int16_t)nbr) : 1;
	size == 4 ? (nbr = (int32_t)nbr) : 1;
	return (nbr * (int64_t)sign);
}

int32_t		ft_label(u_int32_t bytes, t_token *token)
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

void		arg_types_code(t_token *com, u_int32_t *carriage, u_int8_t n_arg)
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
	ft_itoh(tmp, 1, carriage);
}

void		ft_command_in_buf(t_token **com, u_int32_t *carriage, u_int8_t type)
{
	u_int8_t n_arg;
	u_int8_t d_size;

	ft_itoh(g_op_tab[type].code, 1, carriage);
	n_arg = g_op_tab[type].args_num;
	if (g_op_tab[type].args_types_code)
		arg_types_code(*com, carriage, n_arg);
	*com = (*com)->next;
	while (n_arg--)
	{
		while ((*com)->type == Separator)
			*com = (*com)->next;
		d_size = g_op_tab[type].t_dir_size;
		if ((*com)->type == Register)
			ft_itoh(ft_atoi_cor((*com)->content + 1, 1), 1, carriage);
		else if ((*com)->type == Direct)
			ft_itoh(ft_atoi_cor((*com)->content, d_size), d_size, carriage);
		else if ((*com)->type == Indirect)
			ft_itoh(ft_atoi_cor((*com)->content, IND_SIZE), IND_SIZE, carriage);
		else if ((*com)->type == Direct_label)
			ft_itoh(ft_label((*com)->bytes, *com), d_size, carriage);
		else if ((*com)->type == Indirect_label)
			ft_itoh(ft_label((*com)->bytes, *com), IND_SIZE, carriage);
		*com = (*com)->next;
	}
}

void		ft_compilation_champ(void)
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
