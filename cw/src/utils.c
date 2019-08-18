/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:40:53 by larlyne           #+#    #+#             */
/*   Updated: 2019/08/16 12:40:54 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				accurate_read(int fd, char *buffer, int n_bytes)
{
	int readed;
	int i;
	int	no_data;

	if (fd <= 0)
		return (fd);
	no_data = 0;
	i = 0;
	while (i != n_bytes)
	{
		readed = read(fd, buffer + i, n_bytes - i);
		if (readed == 0)
		{
			++no_data;
			if (no_data == 5)
				return (-1);
		}
		else if (readed < 0)
			return (-1);
		else
			i += readed;
	}
	return (n_bytes);
}

int				end_with(char *str, char *end)
{
	int		str_len;
	int		end_len;

	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (end_len > str_len)
		return (0);
	while (end_len >= 0)
		if (str[str_len--] != end[end_len--])
			return (0);
	return (1);
}

void			revert_bytes(void *addr, int size)
{
	int		i;
	char	*caddr;
	char	temp;

	caddr = (char*)addr;
	i = 0;
	while (i < size / 2)
	{
		temp = caddr[i];
		caddr[i] = caddr[size - 1 - i];
		caddr[size - 1 - i] = temp;
		++i;
	}
}

int				regnumber_contains(int reg_n)
{
	return ((1 <= reg_n && reg_n <= REG_NUMBER) ? 1 : 0);
}
