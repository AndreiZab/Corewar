/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_uc_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qclubfoo <qclubfoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:44:41 by qclubfoo          #+#    #+#             */
/*   Updated: 2019/07/16 13:44:58 by qclubfoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>

char	*casting_uc_hex(unsigned char c)
{
	char	*str;
	char	*ret;
	int		i;

	str = "0123456789abcdef";
	if (!(ret = (char*)malloc(sizeof(char) * 3)))
		return (NULL);
	ret[2] = '\0';
	ret[1] = str[c % 16];
	ret[0] = str[(c / 16) % 16];
	str = NULL;
	return (ret);
}

// int	main(void)
// {
// 	unsigned char	c;
// 	char	*str;

// 	c = 256;
// 	str = casting_uc_hex(c);
// 	printf("%s\n", str);
// 	free(str);
// 	str = NULL;
// 	return (0);
// }