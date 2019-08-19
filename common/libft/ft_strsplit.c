/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:56:28 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/12 16:37:55 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	char	was_sep;

	count = 0;
	was_sep = 1;
	while (*s)
	{
		if (*s != c && was_sep)
		{
			was_sep = 0;
			++count;
		}
		else if (*s == c)
			was_sep = 1;
		++s;
	}
	return (count);
}

static size_t	ft_len_to_sep(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		++s;
		++len;
	}
	return (len);
}

static char		*ft_put_word(char const *s, size_t len)
{
	char	*str;

	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy(str, s, len);
	str[len] = '\0';
	return (str);
}

static char		**ft_free_char_arr(char **arr, size_t filled)
{
	size_t	i;

	i = 0;
	while (i < filled)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**word_arr;
	size_t	words;
	size_t	j;
	size_t	current_len;

	if (s == NULL)
		return (NULL);
	words = ft_word_count(s, c);
	if ((word_arr = (char**)malloc(sizeof(char*) * (words + 1))) == NULL)
		return (NULL);
	j = 0;
	while (*s)
	{
		current_len = ft_len_to_sep(s, c);
		if (current_len != 0)
		{
			if ((word_arr[j++] = ft_put_word(s, current_len)) == NULL)
				return (ft_free_char_arr(word_arr, j - 1));
			s += current_len;
		}
		else
			++s;
	}
	word_arr[j] = NULL;
	return (word_arr);
}
