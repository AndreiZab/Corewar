/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_insert_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:01:27 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/04 13:45:01 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstr_insert_s(t_lstr *lstr, char *str, int index)
{
	int	len;

	if (lstr == NULL || str == NULL || index < 0 || index > lstr->length)
		return ;
	len = (int)ft_strlen(str);
	if (lstr->capacity < lstr->length + 1 + len)
		if (!ft_lstr_resize(lstr, lstr->length + len))
			return ;
	if (index != lstr->length)
		ft_memmove(lstr->str + index + len, lstr->str + index,
				lstr->length - index);
	ft_memcpy(lstr->str + index, str, len);
	lstr->length += len;
	lstr->str[lstr->length] = 0;
}
