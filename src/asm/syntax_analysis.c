/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:17:31 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 18:07:10 by rhealitt         ###   ########.fr       */
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

static void			ft_valid_arg(int cmd, t_token *tkn, int cmp, u_int32_t beg)
{
	int				arg_type;

	arg_type = tkn->type;
	if (tkn->type == Direct_label)
		arg_type = T_DIR;
	else if (tkn->type == Indirect_label)
		arg_type = T_IND;
	if (arg_type != (arg_type & cmp))
		ft_error("WRONG_TYPE_OF_ARGUMENT");
	if (arg_type == T_IND || arg_type == T_DIR)
	{
		tkn->bytes = beg;
		if (arg_type == T_IND)
			g_bytes += IND_SIZE;
		else
			g_bytes += g_op_tab[cmd].t_dir_size;
	}
	else if (arg_type == T_REG)
		g_bytes++;
}

static void			ft_valid_command(t_token **command, int i)
{
	int				com_num;
	int32_t			args;
	unsigned int	*types;
	t_token			*token;
	u_int32_t		begin;

	token = (*command);
	com_num = ft_find_cmd(token);
	args = g_op_tab[com_num].args_num;
	types = g_op_tab[com_num].args_types;
	begin = g_bytes;
	g_bytes += 1 + (g_op_tab[com_num].args_types_code ? 1 : 0);
	while ((token = token->next) && token->type < 6 && args--)
	{
		ft_valid_arg(com_num, token, types[i++], begin);
		token = token->next;
		if (token->type != Separator)
			break ;
	}
	if (token && !(token->type == Line_feed || token->type == EOF))
		ft_error("NEED_NEWLINE_IN_EOF");
	if (args != 0)
		ft_error("INVALID_NUM_OF_ARGUMENTS");
	*command = token;
}

void				ft_syntax_champ(void)
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
