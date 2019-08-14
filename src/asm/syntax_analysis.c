/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:17:31 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/14 17:17:31 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void 		ft_syntax_champ(void)
{
	t_token *token;

	token = g_data->tokens;
	while (token)
	{
		if (token->type == Instruction)
			valid_instruction(&token);
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