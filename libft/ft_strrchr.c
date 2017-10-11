/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 07:57:15 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/06 11:37:30 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t len;

	len = ft_strlen(s);
	while (*s)
		s++;
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (len == 0)
			break ;
		s--;
		len--;
	}
	return (NULL);
}
