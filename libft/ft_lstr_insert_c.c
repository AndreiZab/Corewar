/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_insert_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 12:53:44 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/04 12:54:11 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstr_insert_c(t_lstr *lstr, char c, int count, int index)
{
	if (lstr == NULL || count < 1 || index < 0 || index > lstr->length)
		return ;
	if (lstr->capacity < lstr->length + 1 + count)
		if (!ft_lstr_resize(lstr, lstr->length + count))
			return ;
	if (index != lstr->length)
		ft_memmove(lstr->str + index + count, lstr->str + index,
			lstr->length - index + 1);
	ft_memset(lstr->str + index, c, count);
	lstr->length += count;
}
