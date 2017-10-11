/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:00:17 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/01 12:01:02 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int				i;
	unsigned char	*s1ptr;
	unsigned char	*s2ptr;

	i = 0;
	s1ptr = (unsigned char *)str1;
	s2ptr = (unsigned char *)str2;
	while (s1ptr[i] == s2ptr[i] && s1ptr[i] && s2ptr[i])
		i++;
	return (s1ptr[i] - s2ptr[i]);
}
