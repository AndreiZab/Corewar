/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:37:37 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 10:47:51 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*arr;

	if ((len = ft_strlen(s1)) + 1 == 0)
		return (NULL);
	if ((arr = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy((void*)arr, (void*)s1, len + 1);
	return (arr);
}
