/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:28:53 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	*dwblock;
	unsigned int	*wblock;
	unsigned char	*cblock;

	dwblock = (unsigned long*)s;
	while (n >= sizeof(long))
	{
		*dwblock++ = 0;
		n -= sizeof(long);
	}
	wblock = (unsigned int*)dwblock;
	while (n >= sizeof(int))
	{
		*wblock++ = 0;
		n -= sizeof(int);
	}
	cblock = (unsigned char*)wblock;
	while (n--)
		*cblock++ = 0;
}
