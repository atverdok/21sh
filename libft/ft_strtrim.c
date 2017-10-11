/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 07:46:37 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/01 12:23:15 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	char	*end;

	if (s)
	{
		while (is_whitespaces(*s) && *s)
			s++;
		end = ft_strchr(s, 0);
		while (is_whitespaces(*(end - 1)) && end > s)
			end--;
		str = (char *)ft_memalloc(end - s + 1);
		if (str && (end - s))
			ft_memmove(str, s, (end - s));
		return (str);
	}
	return (NULL);
}
