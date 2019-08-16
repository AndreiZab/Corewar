/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:14:10 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 18:27:53 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
#include "get_next_line.h"

int				ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

static int		ft_free_l(char *line)
{
	if (line)
		free(line);
	return (1);
}

static void		ft_row_is_data(char *str, int i)
{
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			return ;
		if (g_data->quotes == 1 || g_data->quotes == 3)
			i = ft_add_text(str, i - 1);
		else
			i = ft_find_name_or_comment(str, i);
		if (str[i])
			i++;
		if (g_data->name && ft_strlen(g_data->name) > PROG_NAME_LENGTH)
			ft_error("NAME_TOO_LONG");
		if (g_data->comment && ft_strlen(g_data->comment) > COMMENT_LENGTH)
			ft_error("COMMENT_TOO_LONG");
	}
}

static void		ft_check_row(char *str)
{
	if (!g_data->comment || !g_data->name || str[g_data->x] == '.'
	|| g_data->quotes == 1 || g_data->quotes == 3)
		ft_row_is_data(str, g_data->x);
	else
		ft_row_is_code(str);
}

static void		ft_read_champ(void)
{
	char	*line;
	int		err;

	line = NULL;
	while (ft_free_l(line) && (err = get_next_line(g_data->fd, &line)) > 0
	&& !(g_data->x = 0) && ++g_data->y)
	{
		if (g_data->tokens)
			ft_token_create(Line_feed);
		while (line[g_data->x] == ' ' || line[g_data->x] == '\t')
			g_data->x++;
		if (line[g_data->x] == COMMENT_CHAR
		|| line[g_data->x] == ALT_COMMENT_CHAR)
			continue ;
		ft_check_row(line);
	}
	ft_token_create(EOF);
	if (g_data->quotes == 1 || g_data->quotes == 3)
		ft_error("ERROR_WITH_QUOTES");
	if (err == -1)
		ft_error("ERROR_READ_FILE");
	else if (!g_data->comment)
		ft_error("NO_COMMENT");
	else if (!g_data->name)
		ft_error("NO_NAME");
}

void			ft_asm(char *str)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) == -1)
		ft_error("FILE_NOT_FOUND");
	ft_create(fd, str);
	ft_read_champ();
	ft_revert_tokens();
	ft_syntax_champ();
	ft_compilation_champ();
	ft_write_bytes();
	if (close(fd) < 0)
		ft_error("CANT_CLOSE_FILE");
	ft_free_data();
}
