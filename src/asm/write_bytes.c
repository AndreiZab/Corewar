/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:33:06 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/15 19:50:00 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char			*new_filename(char *filename)
{
	u_int16_t		len;
	char			*new_name;
	u_int16_t		i;

	len = -1;
	while (filename[++len] + 1)
		if (filename[len] == '.' && filename[len + 1] == 's' && filename[len + 2] == '\0')
			break ;
	if (!(new_name = (char*)ft_memalloc(len + 5)))
		ft_error("NO_MEMORY");
	i = -1;
	while (++i < len)
		new_name[i] = filename[i];
	ft_strcpy(&(new_name[i]), ".cor");
	return (new_name);
}

void				ft_write_bytes(void)
{
	int				fd;
	char			*new_name;

	new_name = new_filename(g_data->filename);
	if ((fd = open(new_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		ft_error("ERROR_CREATING_FILE");
	write(1, "Writing output program to ", 26);
	ft_putendl_fd(new_name, 1);
	free(new_name);
	if (write(fd, g_buf, 2192 + g_bytes) == -1)
	{
		close(fd);
		ft_error("ERROR_WRITING_FILE");
	}
	close(fd);
}