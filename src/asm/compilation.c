/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compilation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:28:01 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 16:38:24 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void	ft_itoh(int32_t dec, int dir_size, u_int32_t *curr)
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
	int				neg;
	int				i;
	int64_t			num;

	i = 0;
	neg = 0;
	num = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '-')
		neg = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += ((int)str[i] - 48);
		i++;
	}
	num = (neg == 1 ? -num : num);
	size == 1 ? (num = (u_int8_t)num) : 1;
	size == 2 ? (num = (int16_t)num) : 1;
	size == 4 ? (num = (int32_t)num) : 1;
	return (num);
}

int32_t	ft_label(u_int32_t bytes, t_token *token)
{
	int32_t	move;
	t_label	*label;

	label = g_data->labels;
	while (label)
	{
		if (!(ft_strcmp(token->content, label->ptr->content)))
			break ;
		label = label->prev; //prev real
	}
	if (!label || !label->ptr)
		ft_error("INVALID_LABEL");
	move = label->ptr->bytes - bytes;
	return (move);
}

void	arg_types_code(t_token *com, u_int32_t *cursor, u_int8_t n_arg)
{
	int8_t	bin;
	int		arg;

	bin = 0;
	arg = 0;
	while (arg < n_arg)
	{
		if (com->type == Register)
			bin |= 1 << 2 * (3 - arg++);
		else if (com->type == Direct || com->type == Direct_label)
			bin |= 2 << 2 * (3 - arg++);
		else if (com->type == Indirect || com->type == Indirect_label)
			bin |= 3 << 2 * (3 - arg++);
		com = com->next;
	}
	ft_itoh(bin, 1, cursor);
}

void	ft_command_in_buf(t_token **com, u_int32_t *cursor, u_int8_t type)
{
	u_int8_t n_arg;
	u_int8_t d_size;

	ft_itoh(g_op_tab[type].code, 1, cursor);
	n_arg = g_op_tab[type].args_num;
	if (g_op_tab[type].args_types_code)
		arg_types_code(*com, cursor, n_arg);
	*com = (*com)->next;
	while (n_arg--)
	{
		while ((*com)->type == Separator)
			*com = (*com)->next;
		d_size = g_op_tab[type].t_dir_size;
		if ((*com)->type == Register)
			ft_itoh(ft_atoi_cor((*com)->content + 1, 1), 1, cursor);
		else if ((*com)->type == Direct)
			ft_itoh(ft_atoi_cor((*com)->content, d_size), d_size, cursor);
		else if ((*com)->type == Indirect)
			ft_itoh(ft_atoi_cor((*com)->content, IND_SIZE), IND_SIZE, cursor);
		else if ((*com)->type == Direct_label)
			ft_itoh(ft_label((*com)->bytes, *com), d_size, cursor);
		else if ((*com)->type == Indirect_label)
			ft_itoh(ft_label((*com)->bytes, *com), IND_SIZE, cursor);
		*com = (*com)->next;
	}
}

void 	ft_compilation_champ(void)
{
	t_token		*token;
	u_int32_t	carriage;

	token = g_data->tokens;
	if (!(g_data->output = (char*)ft_memalloc(sizeof(char) * (2192 + g_bytes)))) // сделать не глобал
		ft_error("NO_MEMORY");
	carriage = 0;
	ft_itoh(COREWAR_EXEC_MAGIC, 4, &carriage);
	carriage = 4 + PROG_NAME_LENGTH + 4;
	ft_itoh(g_bytes, 4, &carriage);
	carriage = 2192;
	ft_memcpy(g_data->output + 4 + PROG_NAME_LENGTH + 4 * 2, g_data->comment, ft_strlen(g_data->comment));
	ft_memcpy(g_data->output + 4, g_data->name, ft_strlen(g_data->name));
	while (token)
	{
		if (token->type == Instruction)
			ft_command_in_buf(&token, &carriage, token->bytes);
		token = token->next;
	}
}