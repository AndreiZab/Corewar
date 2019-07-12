/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:53:33 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/09 09:56:27 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		current_pos;
	int		current_num;
	int		was_digit;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		ft_putchar_fd('-', fd);
	}
	was_digit = 0;
	current_pos = 1000000000;
	while (current_pos != 0)
	{
		current_num = n / current_pos;
		if (was_digit || current_pos == 1 || current_num != 0)
		{
			ft_putchar_fd(current_num * sign + '0', fd);
			was_digit = 1;
		}
		n -= current_num * current_pos;
		current_pos /= 10;
	}
}
