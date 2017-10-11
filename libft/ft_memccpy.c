/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:04:51 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/01 12:08:43 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destptr, const void *srcptr, int c, size_t num)
{
	char	*d;
	char	*src;
	size_t	i;

	d = (char *)destptr;
	src = (char *)srcptr;
	i = 0;
	while (i < num)
	{
		*(d + i) = *(src + i);
		if (*(src + i) == c)
		{
			return ((void *)d + (i + 1));
		}
		i++;
	}
	return (NULL);
}
