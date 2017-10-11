/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:43:07 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/27 17:43:12 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int		is_env(char *name, char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name))
			&& env[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char *name, char **env)
{
	int	index;

	if (*env)
	{
		if ((index = is_env(name, env)) != -1)
			return (env[index] + ft_strlen(name) + 1);
	}
	return (NULL);
}

void	print_env(char **env)
{
	while (*env != NULL)
	{
		ft_putstr(*env);
		ft_putchar('\n');
		env++;
	}
}

char	*get_value_env(char **str, char **env)
{
	char	*str_ptr;
	char	*env_name;
	char	*env_str;
	size_t	end;

	str_ptr = *str;
	end = 0;
	env_str = "";
	while (ft_isalnum(*str_ptr) || *str_ptr == '_')
	{
		end++;
		str_ptr++;
	}
	if (end)
	{
		env_name = ft_strsub(*str, 0, end);
		if (*env_name && ((env_str = ft_getenv(env_name, env)) == NULL))
			env_str = "";
		ft_strdel(&env_name);
	}
	else
		env_str = "$";
	(*str) += end;
	return (env_str);
}
