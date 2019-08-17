/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:16:55 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 10:55:10 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	if (len + 1 == 0)
		return (NULL);
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy((void*)str, (const void*)s + start, len);
	*(str + len) = '\0';
	return (str);
}
