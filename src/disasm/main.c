#include "disasm.h"

int		disasm(char *filename, char colored)
{
	int		fd;
	int		code_size;

	code_size = 0;
	if (!end_with(filename, ".cor"))
		return (print_error(".cor file expected", colored));
	if ((fd = open(filename, O_RDONLY)) <= 0)
		return (print_error("Can't open this file", colored));
	if (!check_magic_header(fd, colored))
		return (close(fd) & 0);
	if (!check_name(fd, colored))
		return (close(fd) & 0);
	if (!check_null(fd, colored))
		return (close(fd) & 0);
	if (!check_code_size(fd, &code_size, colored))
		return (close(fd) & 0);
	if (!check_comment(fd, colored))
		return (close(fd) & 0);
	if (!check_null(fd, colored))
		return (close(fd) & 0);
	if (!check_exe(fd, code_size, colored))
		return(close(fd) & 0);
	check_eof(fd, colored);
	return (close(fd));
}

int		main(int argc, char **argv)
{
	int		i;
	char	colored;

	colored = 0;
	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "-c") == 0))
		ft_putstr("usage: ./disasm [-c] [filename1.cor ...]\n");
	else
	{
		i = 0;
		if (ft_strcmp(argv[1], "-c") == 0)
			colored = ++i;
		while (++i < argc)
		{
			if (argc != 2 + colored)
			{
				if (i > 1 + colored)
					ft_putchar('\n');
				print_filename(argv[i], colored);
			}
			disasm(argv[i], colored);
		}	
	}
	return (0);
}
