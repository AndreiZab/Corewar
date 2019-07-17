/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_is_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 11:56:21 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/17 17:04:16 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int i;
	char *subs;

	if (s == NULL)
		return (NULL);
	if (!(subs = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (len--)
	{
		subs[i] = s[start + i];
		i++;
	}
	return (subs);
}

t_token			*ft_token_create(void)
{
	t_token *token;

	if (!(token = (t_token *) malloc(sizeof(t_token))))
		ft_error("NO_MEMORY", NULL);
	token->row = 0;
	token->content = NULL;
	token->type = 0;
	return (token);
}

char	g_commands[REG_NUMBER][6] = {
		"lfork",
		"sti",
		"fork",
		"lld",
		"ld",
		"add",
		"zjmp",
		"sub",
		"ldi",
		"or",
		"st",
		"aff",
		"live",
		"xor",
		"lldi",
		"and"
};

int 		ft_len_one_word(char *str)
{
	int i;

	i = 0;
	if (str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
		i += 2;
	else if (str[0] == LABEL_CHAR)
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != COMMENT_CHAR && str[i] != ALT_COMMENT_CHAR && str[i] != LABEL_CHAR && str[i] != SEPARATOR_CHAR)
		i++;
	if (str[i] == LABEL_CHAR && i != 0)
		i++;
	if (str[0] == SEPARATOR_CHAR && i == 0)
		i++;
	if (i > 0)
		return (i);
	if (str[i] == ' ' || str[i] == '\t')
		return (1);
	return (0);
}

int			ft_check_label_chars(char *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i] && str[i] != LABEL_CHAR)
	{
		j = -1;
		while  (LABEL_CHARS[++j])
			if (LABEL_CHARS[j] == str[i])
				break;
		if (!LABEL_CHARS[j])
			return (0);
	}
	return (1);
}

int			ft_check_label_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == LABEL_CHAR || str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return (1);
		i++;
	}
	return (0);
}

void		ft_parse_token(t_data *data, char *str, t_token	*token)
{
	token->content = str;
	if (str[0] == ' ' || str[0] == '\t')
		token->type = Whitespace;
	else if (str[0] == SEPARATOR_CHAR)
		token->type = Separator;
	else if (str[0] != DIRECT_CHAR && ft_check_label_char(str))
	{
		if (ft_check_label_chars(str))
			token->type = Label;
		else
			ft_error("WRONG_SYMBOL_IN_LABEL", data);
	}
	else
		ft_is_digits(data, str, token);
}

void		ft_row_is_code (t_data *data, char *str)
{
	int i;
	int len;
	t_token	*token;

	i = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return ;
		len = ft_len_one_word(str + i);
		token = ft_token_create();
		token->row = data->num_current_row;
		ft_parse_token(data, ft_strsub(str, i, len), token);
		i += len;
	}

}