/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcolor_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 11:53:11 by rhealitt          #+#    #+#             */
/*   Updated: 2019/08/19 11:53:11 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_setcolor_fd(int fd, t_ccolor backg, t_ccolor foreg)
{
	if (fd <= 0 || (backg == cc_current && foreg == cc_current))
		return ;
	ft_putstr_fd("\033[", fd);
	if (backg != cc_current)
	{
		ft_putchar_fd('4', fd);
		ft_putchar_fd('0' + backg, fd);
	}
	if (foreg != cc_current)
	{
		if (backg != cc_current)
			ft_putchar_fd(';', fd);
		ft_putchar_fd('3', fd);
		ft_putchar_fd('0' + foreg, fd);
	}
	ft_putchar_fd('m', fd);
}
