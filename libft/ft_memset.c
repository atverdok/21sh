/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 13:08:58 by atverdok          #+#    #+#             */
/*   Updated: 2016/11/24 13:53:24 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	char *m;

	m = memptr;
	if (num)
	{
		while (num > 0)
		{
			*m = val;
			m++;
			num--;
		}
	}
	return (memptr);
}
