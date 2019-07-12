/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:32:38 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/14 10:35:48 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_realloc(void *src, size_t old_size, size_t new_size)
{
	void	*dst;

	if (src == NULL)
		return (NULL);
	dst = NULL;
	if (new_size != 0)
	{
		if ((dst = malloc(new_size)) == NULL)
			return (NULL);
		ft_memcpy(dst, src, (old_size < new_size) ? old_size : new_size);
	}
	free(src);
	return (dst);
}
