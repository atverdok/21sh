/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:34:29 by atverdok          #+#    #+#             */
/*   Updated: 2016/11/29 15:42:44 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;

	if (s)
	{
		str = (char *)ft_memalloc(len + 1);
		if (str)
		{
			return (ft_strncpy(str, s + start, len));
		}
	}
	return (NULL);
}
