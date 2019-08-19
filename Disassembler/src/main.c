/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:55:36 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/18 15:52:17 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static int		try_set_option(char flag, char *opt)
{
	if (flag == 'c')
		*opt |= DISASM_OPT_COLORS;
	else if (flag == 'f')
		*opt |= DISASM_OPT_FILE_FORMAT;
	else
		return (0);
	return (1);
}

static int		get_options(int argc, char **argv, char *opt)
{
	int		i;
	int		j;
	int		files_cnt;

	files_cnt = 0;
	i = 0;
	while (++i < argc)
		if (argv[i][0] == '-')
		{
			j = -0;
			while (argv[i][++j])
			{
				if (!try_set_option(argv[i][j], opt))
					return (print_usage());
			}
		}
		else
			++files_cnt;
	if (files_cnt == 0)
		return (print_error("No files in arguments", *opt));
	return (files_cnt);
}

static void		load_checks(int (*checks[8])(int fd, char colored, void *arg))
{
	checks[0] = check_magic_header;
	checks[1] = check_name;
	checks[2] = check_null;
	checks[3] = check_code_size;
	checks[4] = check_comment;
	checks[5] = check_null;
	checks[6] = check_exe;
	checks[7] = check_eof;
}

static int		disasm(char *filename, char options, int (*checks[8])
					(int fd, char colored, void *arg))
{
	int		fd;
	int		code_size;
	int		i;

	if (options & DISASM_OPT_FILENAME)
		print_filename(filename, options);
	code_size = 0;
	if (!end_with(filename, ".cor"))
		return (print_error(".cor file expected", options));
	if ((fd = open(filename, O_RDONLY)) <= 0)
		return (print_error("Can't open this file", options));
	i = -1;
	while (++i < 8)
		if (!checks[i](fd, options, &code_size))
			return (close(fd) & 0);
	return (close(fd));
}

int				main(int argc, char **argv)
{
	int		(*checks[8])(int fd, char colored, void *arg);
	int		i;
	char	options;
	int		files;

	options = 0;
	if (argc == 1)
		return (print_usage());
	if ((files = get_options(argc, argv, &options)) == 0)
		return (0);
	options |= (files > 1) ? DISASM_OPT_FILENAME : 0;
	load_checks(checks);
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			disasm(argv[i], options, checks);
		if (argv[i][0] != '-' && (files-- > 1 ||
			options & DISASM_OPT_FILE_FORMAT))
			ft_putchar('\n');
	}
	return (0);
}
