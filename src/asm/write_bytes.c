/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:33:06 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/16 16:05:23 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"


char			*ft_new_file(char *s_name)
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
	if (write(fd, g_buf, 2192 + g_bytes) == 2192 + g_bytes && close(fd) == 0)
		;
	else
		ft_error("ERROR_WRITING_FILE");
}