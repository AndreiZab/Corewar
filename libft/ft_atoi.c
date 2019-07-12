/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:14:27 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/14 09:33:05 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	numb;
	char	sign;
	char	was_sign;

	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		++i;
	was_sign = sign;
	numb = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		numb = numb * 10 + (str[i++] - '0');
		if (numb < 0 && was_sign == 1)
			return (-1);
		else if (numb < 0 && was_sign == -1)
			return (0);
	}
	return ((int)numb * sign);
}
