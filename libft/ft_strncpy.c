/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:39:34 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/06 12:38:13 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char *ptr_dst;

	ptr_dst = dst;
	while (n > 0 && *src != '\0')
	{
		*ptr_dst++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*ptr_dst++ = '\0';
		n--;
	}
	return (dst);
}
