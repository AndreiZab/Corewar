/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_insert_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:01:27 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/04 13:01:29 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstr_insert_sn(t_lstr *lstr, char *str, int len, int index)
{
	int	str_len;

	if (lstr == NULL || str == NULL || index < 0 || index > lstr->length)
		return ;
	str_len = (int)ft_strlen(str);
	if (str_len < len)
		len = str_len;
	if (lstr->capacity < lstr->length + 1 + len)
		if (!ft_lstr_resize(lstr, lstr->length + len))
			return ;
	if (index != lstr->length)
		ft_memmove(lstr->str + index + len, lstr->str + index,
			lstr->length - index);
	ft_memcpy(lstr->str + index, str, len);
	lstr->length += len;
}
