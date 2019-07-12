/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstr_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:25:55 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	ft_lstr_destroy(t_lstr **lstr)
{
	if (lstr == NULL || *lstr == NULL)
		return ;
	free((*lstr)->str);
	free(*lstr);
	*lstr = NULL;
}
