/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:10:03 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/15 10:10:05 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int		ft_isint(const char *str)
{
	long long int	num;
	int				sign;

	num = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		++str;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	while ('0' <= *str && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		if ((sign == -1 && -num < INT_MIN) || (sign == 1 && num > INT_MAX))
			return (0);
		++str;
	}
	if (*str != '\0')
		return (0);
	return (1);
}
