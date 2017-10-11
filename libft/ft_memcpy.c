/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:32:31 by atverdok          #+#    #+#             */
/*   Updated: 2016/11/24 15:32:32 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destptr, const void *srcptr, size_t num)
{
	char	*d;
	char	*src;
	size_t	i;

	d = (char *)destptr;
	src = (char *)srcptr;
	i = 0;
	while (i < num)
	{
		d[i] = src[i];
		i++;
	}
	return ((void *)destptr);
}
