/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_uc_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:44:41 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/07/26 14:25:49 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cw.h"

static int		count_rate(int num)
{
	int	rate;

	rate = 1;
	while (num >= 16)
	{
		rate++;
		num /= 16;
	}
	return (rate);
}

static char		*ft_width_less(int num, int rate)
{
	char	*str;
	char	*hex_str;

	if (!(str = (char*)malloc(sizeof(char) * (rate + 1))))
		return (NULL);
	str[rate] = '\0';
	hex_str = "0123456789abcdef";
	while (rate)
	{
		str[--rate] = hex_str[(num % 16)];
		num /= 16;
	}
	return (str);
}

static char		*ft_width_more(int num, int rate, int width)
{
	char	*str;
	char	*hex_str;
	int		i;

	if (!(str = (char*)malloc(sizeof(char) * (width + 1))))
		return (NULL);
	str[width] = '\0';
	hex_str = "0123456789abcdef";
	i = 0;
	while (i < width - rate)
		str[i++] = '0';
	i = width - 1;
	while (i >= width - rate)
	{
		str[i--] = hex_str[(num % 16)];
		num /= 16;
	}
	return (str);
}

static char		*ft_num_zero(int width)
{
	char	*str;
	int		i;

	if (width > 0)
	{
		if (!(str = (char*)malloc(sizeof(char) * (width + 1))))
			return (NULL);
		str[width] = '\0';
		while (--width >= 0)
			str[width] = '0';
	}
	else
	{
		if (!(str = (char*)malloc(sizeof(char) * 2)))
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
	}
	return (str);
}

char			*casting_uc_hex(int num, int width)
{
	int		rate;

	rate = count_rate(num);
	if (num < 0)
		return (NULL);
	if (num == 0)
		return (ft_num_zero(width));
	if (width < 0 || width < rate)
		return (ft_width_less(num, rate));
	else
		return (ft_width_more(num, rate, width));
}
