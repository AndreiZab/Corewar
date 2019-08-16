/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:54:48 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 14:26:33 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		check_magic_header(int fd, char options, void *arg)
{
	char	buff[5];
	int		readed;

	(void)arg;
	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error("Can't read magic header", options));
	revert_bytes(buff, 4);
	readed = *((int*)buff);
	if (readed != COREWAR_EXEC_MAGIC)
		return (print_error("Invalid magic header", options));
	return (1);
}

int		check_name(int fd, char options, void *arg)
{
	char	buff[PROG_NAME_LENGTH + 1];

	(void)arg;
	if (accurate_read(fd, buff, PROG_NAME_LENGTH) <= 0)
		return (print_error("Can't read champion's name", options));
	buff[PROG_NAME_LENGTH] = '\0';
	print_name(buff, options);
	return (1);
}

int		check_null(int fd, char options, void *arg)
{
	char	buff[5];
	int		readed;

	(void)arg;
	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error("Can't read control null", options));
	readed = *((int*)buff);
	if (readed != 0)
		return (print_error("Control null isn't null XD", options));
	return (1);
}

int		check_code_size(int fd, char options, void *arg)
{
	char	buff[5];
	int		*code_size;

	code_size = (int*)arg;
	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error("Can't read code size", options));
	revert_bytes(buff, 4);
	*code_size = *((int*)buff);
	print_code_size(*code_size, options);
	if (*code_size > CHAMP_MAX_SIZE)
		print_warning("Code size greater than current CHAMP_MAX_SIZE!",
			options);
	if (*code_size > MEM_SIZE)
		print_warning("Code size greater than current MEM_SIZE!!!", options);
	return (1);
}

int		check_comment(int fd, char options, void *arg)
{
	char	buff[COMMENT_LENGTH + 1];

	(void)arg;
	if (accurate_read(fd, buff, COMMENT_LENGTH) <= 0)
		return (print_error("Can't read champion's comment", options));
	buff[COMMENT_LENGTH] = '\0';
	print_comment(buff, options);
	return (1);
}
