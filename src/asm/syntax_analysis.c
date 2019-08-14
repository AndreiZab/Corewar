/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:17:31 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/14 19:19:31 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static int			ft_find_cmd(t_token *operation)
{
	int				i;

	i = 0;
	while (i < 16)
		if (!ft_strcmp(operation->content, g_op_tab[i].name))
			break ;
		else
			i++;
	if (i == 16)
		ft_error("INVALID_COMMAND");
	operation->bytes = i;
	return (i);
}

static void			valid_arg(int num_c, t_token *arg, int mask, u_int32_t b_start)
{
	int				arg_type;

	arg_type = arg->type;
	if (arg->type == Direct_label)
		arg_type = T_DIR;
	else if (arg->type == Inderect_label)
		arg_type = T_IND;
	if (arg_type != (arg_type & mask))
		error_token(ERR_ARGTP, arg);
	if (arg_type == T_REG)
		g_bytes++;
	else if (arg_type == T_IND)
	{
		g_bytes += IND_SIZE;
		arg->bytes = b_start;
	}
	else if (arg_type == T_DIR)
	{
		g_bytes += g_op_tab[num_c].t_dir_size;
		arg->bytes = b_start;
	}
}

static void			ft_valid_command(t_token **operations, int i)
{
	int				num_c;
	unsigned char	arg;
	char			*type;
	t_token			*cmd;
	u_int32_t		byte_s;

	byte_s = g_bytes;
	cmd = (*operations);
	num_c = ft_find_cmd(cmd);
	arg = g_op_tab[num_c].args_num;
	type = g_op_tab[num_c].args_types;
	g_bytes += 1 + (g_op_tab[num_c].args_types_code ? 1 : 0);
	while ((cmd = cmd->next) && (cmd->type == Register || cmd->type == Direct || cmd->type == Direct_label || cmd->type == Indirect || cmd->type == Inderect_label)&& arg--)
	{
		valid_arg(num_c, cmd, type[i++], byte_s);
		cmd = cmd->next;
		if (cmd->type != Separator)
			break ;
	}
	if (arg != 0)
		ft_error("INVALID_NUM_OF_ARGUMENTS");
	if (cmd && !(cmd->type == Line_feed || cmd->type == EOF))
		ft_error("NEED_NEWLINE_IN_EOF");
	*operations = cmd;
}

void 		ft_syntax_champ(void)
{
	t_token *token;

	token = g_data->tokens;
	while (token)
	{
		if (token->type == Instruction)
			ft_valid_command(&token, 0);
		else if (token->type == Label)
			token->bytes = g_bytes;
		else if (token->type == Line_feed)
			;
		else if (token->type == EOF)
			break ;
		else
			ft_error("SYNTAX_ERROR");
		token = token->next;
	}
}