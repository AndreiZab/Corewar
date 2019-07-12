/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:38:02 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*char_s;
	unsigned char	char_c;
	unsigned char	*end;

	char_c = (unsigned char)c;
	char_s = (unsigned char*)s;
	end = char_s + n;
	while (char_s != end)
	{
		if (*char_s == char_c)
			return (char_s);
		++char_s;
	}
	return (NULL);
}
