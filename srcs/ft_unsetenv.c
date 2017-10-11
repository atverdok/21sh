/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 04:21:46 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:21:51 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int	ft_unsetenv(char *name, char **env)
{
	int		i;
	size_t	len;

	len = (size_t)len_arr_str(env);
	if ((i = is_env(name, env)) != -1)
	{
		free(env[i]);
		ft_memmove((env + i), (env + i + 1), ((len - i) * sizeof(char *)));
		return (0);
	}
	return (-1);
}

int	make_unsetenv(char **args, char **env)
{
	int i;

	i = 1;
	while (args[i] != NULL)
	{
		ft_unsetenv(args[i], env);
		i++;
	}
	return (1);
}
