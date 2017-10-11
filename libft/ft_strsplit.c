/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:19:57 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/01 12:16:19 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		len_item(char const *s, char c)
{
	size_t len;

	len = 0;
	while (*s != c && *s != 0)
	{
		len++;
		s++;
	}
	return (len);
}

static const char	*next_item(char const *str, char c)
{
	while (*str == c)
		str++;
	return (str);
}

static size_t		count_items(char const *s, char c)
{
	size_t value;
	size_t l_item;

	value = 0;
	s = next_item(s, c);
	while (*s)
	{
		l_item = len_item(s, c);
		s = next_item(s + l_item, c);
		value++;
	}
	return (value);
}

static char			*add_item(char const *s, char c)
{
	char	*item_ptr;
	size_t	l_item;

	l_item = len_item(next_item(s, c), c);
	item_ptr = (char *)ft_memalloc(l_item + 1);
	if (!item_ptr)
		return (NULL);
	return (ft_strncpy(item_ptr, s, l_item));
}

char				**ft_strsplit(char const *s, char c)
{
	char	**arr;
	size_t	l_item;
	size_t	i;
	size_t	c_items;

	if (!s)
		return (NULL);
	c_items = count_items(s, c);
	arr = (char **)ft_memalloc(sizeof(char *) * (c_items + 1));
	i = 0;
	l_item = 0;
	if (arr)
	{
		while (i < c_items)
		{
			s = next_item(s + l_item, c);
			arr[i] = add_item(s, c);
			l_item = len_item(s, c);
			i++;
		}
	}
	return (arr);
}
