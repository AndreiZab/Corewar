/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_from_raw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:20:38 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

t_lstr	*ft_lstr_new_raw(char *str)
{
	t_lstr	*lstr;
	int		len;

	len = (int)ft_strlen(str);
	if (len == 0)
		return (ft_lstr_new_empty());
	if ((lstr = (t_lstr*)malloc(sizeof(t_lstr))) == NULL)
		return (NULL);
	lstr->str = str;
	lstr->length = len;
	lstr->capacity = len + 1;
	return (lstr);
}
