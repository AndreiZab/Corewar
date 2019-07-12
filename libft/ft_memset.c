/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:23:24 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/14 09:50:17 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cblock;
	unsigned char	uc;

	uc = (unsigned char)c;
	cblock = (unsigned char*)b;
	while (len--)
		*cblock++ = uc;
	return (b);
}
