/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 10:12:51 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/30 10:12:54 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include "libft.h"

int		ft_putstrn_fd(int fd, char *str, int n)
{
	if (n <= 0)
		return (0);
	write(fd, str, n);
	return (n);
}
