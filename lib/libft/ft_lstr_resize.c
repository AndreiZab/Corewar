/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:38:45 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/02 11:38:47 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

int		ft_lstr_resize(t_lstr *lstr, int new_length)
{
	char	*str;

	if (lstr == NULL || new_length + 1 <= 0)
		return (0);
	str = ft_realloc(lstr->str, lstr->length + 1, new_length + 1);
	if (str == NULL)
		return (0);
	lstr->capacity = new_length + 1;
	lstr->str = str;
	return (1);
}
