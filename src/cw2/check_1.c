/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:54:15 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 15:59:57 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_magic_header(int fd, t_corewar *cw, t_player *pl)
{
	char	buff[5];
	int		readed;

	(void)pl;
	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error_file("Can't read magic header", cw));
	revert_bytes(buff, 4);
	readed = *((int*)buff);
	if (readed != COREWAR_EXEC_MAGIC)
		return (print_error_file("Invalid magic header", cw));
	return (COREWAR_STATUS_OK);
}

int		check_name(int fd, t_corewar *cw, t_player *pl)
{
	char	buff[PROG_NAME_LENGTH + 1];

	if (accurate_read(fd, buff, PROG_NAME_LENGTH) <= 0)
		return (print_error_file("Can't read champion's name", cw));
	buff[PROG_NAME_LENGTH] = '\0';
	if ((pl->name = ft_strdup(buff)) == NULL)
		return (print_error("Corewar Memory Error", cw));
	return (COREWAR_STATUS_OK);
}

int		check_null(int fd, t_corewar *cw, t_player *pl)
{
	char	buff[5];
	int		readed;

	(void)pl;
	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error_file("Can't read control null", cw));
	readed = *((int*)buff);
	if (readed != 0)
		return (print_error_file("Control null isn't null XD", cw));
	return (COREWAR_STATUS_OK);
}

int		check_code_size(int fd, t_corewar *cw, t_player *pl)
{
	char	buff[5];

	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error_file("Can't read code size", cw));
	revert_bytes(buff, 4);
	pl->size = *((int*)buff);
	if (pl->size > CHAMP_MAX_SIZE)
		return (print_error_file("Code size greater CHAMP_MAX_SIZE!", cw));
	return (COREWAR_STATUS_OK);
}

int		check_comment(int fd, t_corewar *cw, t_player *pl)
{
	char	buff[COMMENT_LENGTH + 1];

	if (accurate_read(fd, buff, COMMENT_LENGTH) <= 0)
		return (print_error_file("Can't read champion's comment", cw));
	buff[COMMENT_LENGTH] = '\0';
	if ((pl->comment = ft_strdup(buff)) == NULL)
		return (print_error("Corewar Memory Error", cw));
	return (COREWAR_STATUS_OK);
}
