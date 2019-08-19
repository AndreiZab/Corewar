/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_minimize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:37:50 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstr_minimize(t_lstr *lstr)
{
	if (lstr == NULL)
		return ;
	if (lstr->length + 1 < lstr->capacity)
		ft_lstr_resize(lstr, lstr->length);
}
