#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		ft_putstr_ret(char *str, int ret)
{
	while (*str)
		write(1, str++, 1);
	return (ret);
}

char	*casting_uc_hex(unsigned char c)
{
	char	*str;
	char	*ret;
	int		i;

	str = "0123456789abcdef";
	if (!(ret = (char*)malloc(sizeof(char) * 3)))
		return (NULL);
	ret[2] = '\0';
	ret[1] = str[c % 16];
	ret[0] = str[(c / 16) % 16];
	str = NULL;
	return (ret);
}

int		main(int argc, char **argv)
{
	int		readed;
	unsigned char	buffer[1024];
	int		fd;
	int		i;
	char	*hex;

	if (argc != 2)
		return (ft_putstr_ret("usage: ./binr <file>\n", -1));
	if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (ft_putstr_ret("Can't read this file\n", -2));
	while ((readed = read(fd, buffer, 1023)) > 0)
	{
		i = -1;
		while (++i < readed)
		{
			if (i != 0)
				ft_putstr_ret(" ", 0);
			hex = casting_uc_hex(buffer[i]);
			ft_putstr_ret(hex, 0);
			free(hex);
		}
	}
	close(fd);
	return (0);
}