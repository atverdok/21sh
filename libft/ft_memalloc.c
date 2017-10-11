/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 08:02:29 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/01 12:22:36 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *mem_ptr;

	mem_ptr = (char *)malloc(size);
	if (mem_ptr)
	{
		ft_bzero(mem_ptr, size);
		return ((void *)mem_ptr);
	}
	return (NULL);
}
