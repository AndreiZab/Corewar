/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:33:06 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 17:52:04 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void		ft_itoh(int32_t dec, int dir_size, u_int32_t *curr)
{
	int			step;
	int			start_size;

	start_size = dir_size;
	step = 0;
	while (dir_size)
	{
		g_data->output[*curr + dir_size - 1] = (u_int8_t)((dec >> step) & 0xFF);
		step += 8;
		dir_size--;
	}
	*curr += start_size;
}

int32_t		ft_atoi_cor(const char *str, u_int8_t size)
{
	int				sign;
	int				i;
	int64_t			nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ('0' <= str[i] && str[i] <= '9')
		nbr = nbr * 10 + ((int)str[i++] - '0');
	size == 1 ? (nbr = (u_int8_t)nbr) : 1;
	size == 2 ? (nbr = (int16_t)nbr) : 1;
	size == 4 ? (nbr = (int32_t)nbr) : 1;
	return (nbr * (int64_t)sign);
}
static char			*ft_new_file(char *s_name)
{
	u_int16_t		len;
	char			*cor_name;
	u_int16_t		i;

	len = ft_strlen(s_name);
	if (!(cor_name = (char*)ft_memalloc(len + 3)))
		ft_error("NO_MEMORY");
	i = -1;
	while (++i < len - 2)
		cor_name[i] = s_name[i];
	ft_strcpy(&(cor_name[i]), ".cor");
	return (cor_name);
}

void				ft_write_bytes(void)
{
	int				fd;
	char			*cor_name;

	cor_name = ft_new_file(g_data->filename);
	if ((fd = open(cor_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		ft_error("ERROR_CREATING_FILE");
	write(1, "Writing output program to ", 26);
	ft_putendl_fd(cor_name, 1);
	free(cor_name);
	if (write(fd, g_data->output, 2192 + g_bytes) == 2192 + g_bytes
	&& close(fd) == 0)
		;
	else
		ft_error("ERROR_WRITING_FILE");
}
