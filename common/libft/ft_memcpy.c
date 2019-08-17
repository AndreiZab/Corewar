/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:16:21 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long	*wdst;
	unsigned long	*wsrc;
	unsigned char	*cdst;
	unsigned char	*csrc;

	wdst = (unsigned long*)dst;
	wsrc = (unsigned long*)src;
	while (n >= sizeof(long))
	{
		*(wdst++) = *(wsrc++);
		n -= sizeof(long);
	}
	cdst = (unsigned char*)wdst;
	csrc = (unsigned char*)wsrc;
	while (n--)
		*(cdst++) = *(csrc++);
	return (dst);
}
