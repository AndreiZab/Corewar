/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 13:18:57 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 10:50:29 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 + len2 + 1 == 0)
		return (NULL);
	if ((str = (char*)malloc(len1 + len2 + 1)) == NULL)
		return (NULL);
	str = str + len1 + len2;
	*str = '\0';
	while (len2)
		*(--str) = s2[--len2];
	while (len1)
		*(--str) = s1[--len1];
	return (str);
}
