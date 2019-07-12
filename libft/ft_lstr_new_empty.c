/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:10:53 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/02 11:10:59 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

t_lstr		*ft_lstr_new_empty(void)
{
	t_lstr	*lstr;

	if ((lstr = (t_lstr*)malloc(sizeof(t_lstr))) == NULL)
		return (NULL);
	if ((lstr->str = (char*)ft_memalloc(1)) == NULL)
	{
		free(lstr);
		return (NULL);
	}
	lstr->length = 0;
	lstr->capacity = 1;
	return (lstr);
}
