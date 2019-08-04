#include "disasm.h"

int		check_magic_header(int fd, char colored)
{
	char	buff[5];
	int		readed;

	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error("Can't read magic header", colored));
	revert_bytes(buff, 4);
	readed = *((int*)buff);
	if (readed != COREWAR_EXEC_MAGIC)
		return (print_error("Invalid magic header", colored));
	return (1);
}

int		check_name(int fd, char colored)
{
	char	buff[PROG_NAME_LENGTH + 1];

	if (accurate_read(fd, buff, PROG_NAME_LENGTH) <= 0)
		return (print_error("Can't read champion's name", colored));
	buff[PROG_NAME_LENGTH] = '\0';
	print_name(buff, colored);
	return (1);
}

int		check_null(int fd, char colored)
{
	char	buff[5];
	int		readed;

	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error("Can't read control null", colored));
	readed = *((int*)buff);
	if (readed != 0)
		return (print_error("Control null isn't null XD", colored));
	return (1);
}

int		check_code_size(int fd, int *code_size, char colored)
{
	char	buff[5];

	if (accurate_read(fd, buff, 4) <= 0)
		return (print_error("Can't read code size", colored));
	revert_bytes(buff, 4);
	*code_size = *((int*)buff);
	print_code_size(*code_size, colored);
	if (*code_size > CHAMP_MAX_SIZE)
		print_warning("Code size greater than current CHAMP_MAX_SIZE!", colored);
	if (*code_size > MEM_SIZE)
		print_warning("Code size greater than current MEM_SIZE!!!", colored);
	return (1);
}

int		check_comment(int fd, char colored)
{
	char	buff[COMMENT_LENGTH + 1];

	if (accurate_read(fd, buff, COMMENT_LENGTH) <= 0)
		return (print_error("Can't read champion's comment", colored));
	buff[COMMENT_LENGTH] = '\0';
	print_comment(buff, colored);
	return (1);
}
