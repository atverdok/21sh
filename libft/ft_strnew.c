/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 08:47:20 by atverdok          #+#    #+#             */
/*   Updated: 2016/11/29 09:22:47 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *mem_ptr;

	mem_ptr = (char *)malloc(size + 1);
	if (mem_ptr)
	{
		ft_bzero(mem_ptr, size + 1);
		return (mem_ptr);
	}
	return (NULL);
}
