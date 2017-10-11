/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ft_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 07:00:47 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 07:01:33 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int		ft_strequ_case_insen(char const *s1, char const *s2)
{
	if (s1 && s2)
	{
		while (ft_tolower(*s1) == ft_tolower(*s2))
		{
			if (*s1 == '\0' && *s2 == '\0')
				return (1);
			s1++;
			s2++;
		}
	}
	return (0);
}
