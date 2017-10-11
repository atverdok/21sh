/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:17:10 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/27 14:33:32 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char	*ft_del_strstr(char *str, char *str2)
{
	char	*str_ptr;
	size_t	len_str2;

	len_str2 = ft_strlen(str2);
	while ((str_ptr = ft_strstr(str, str2)) != NULL)
	{
		ft_memmove(str_ptr, (str_ptr + len_str2), ft_strlen(str_ptr));
	}
	return (str);
}

char	**ft_split_del(char *str, char *delim)
{
	size_t	buf_size;
	int		i;
	char	**args;
	char	*arg;

	buf_size = BUF_SIZE;
	args = ft_memalloc(sizeof(char *) * buf_size);
	i = 0;
	str = ft_del_strstr(str, "\\\n");
	arg = ft_strtok_quote(str, delim);
	while (arg != NULL)
	{
		args[i] = arg;
		i++;
		if ((size_t)i >= buf_size)
		{
			buf_size += BUF_SIZE;
			args = ft_realoc(args, (sizeof(char *) * buf_size));
		}
		arg = ft_strtok_quote(NULL, delim);
	}
	args[i] = NULL;
	return (args);
}
