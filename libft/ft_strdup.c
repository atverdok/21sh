/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:45:59 by atverdok          #+#    #+#             */
/*   Updated: 2016/11/25 11:50:32 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*n_string;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	n_string = (char *)malloc(len + 1);
	if (!n_string)
		return (NULL);
	while (str[i] != '\0')
	{
		n_string[i] = str[i];
		i++;
	}
	n_string[i] = '\0';
	return (n_string);
}
