/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:21:47 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 11:08:56 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*csrc;
	char	*cdst;
	char	*cbuff;
	char	offset;

	if (dst < src)
	{
		csrc = (char*)src;
		cdst = (char*)dst;
		offset = 1;
	}
	else
	{
		csrc = (char*)src + len - 1;
		cdst = (char*)dst + len - 1;
		offset = -1;
	}
	while (len--)
	{
		*cdst = *csrc;
		cdst += offset;
		csrc += offset;
	}
	return (dst);
}
