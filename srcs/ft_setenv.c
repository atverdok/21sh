/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 04:21:16 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:21:20 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int		valid_env_name(char *name)
{
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

char	*row_env(char *name, char *value)
{
	char *row;

	value = (value) ? value : "\0";
	row = ft_strnew(ft_strlen(name) + ft_strlen(value) + 1);
	row = ft_strcpy(row, name);
	row = ft_strcat(row, "=");
	row = ft_strcat(row, value);
	return (row);
}

int		make_valid_name(char *name)
{
	if (!valid_env_name(name))
	{
		ft_print_error("ft_setenv: ", name, ERR_NVITC);
		return (-1);
	}
	return (0);
}

int		ft_setenv(char *name, char *value, int ov, char **env)
{
	int i;
	int flag;

	if (make_valid_name(name) == -1)
		return (-1);
	flag = 0;
	if (name && *name != '\0')
	{
		if ((i = is_env(name, env)) == -1)
		{
			i = len_arr_str(env);
			flag = 1;
		}
		if (ov && !flag)
		{
			ft_strdel(&env[i]);
			env[i] = row_env(name, value);
			return (0);
		}
		env[i] = row_env(name, value);
		return (0);
	}
	ft_print_error("ft_setenv: ", "=", ERR_IA);
	return (-1);
}

int		make_setenv(char **args, char **env)
{
	int		i;
	char	*arg_ptr;

	i = 1;
	arg_ptr = NULL;
	while (args[i]
			&& ((args[i][0] != '=' || !ft_strcmp(args[i], "="))
				&& ((arg_ptr = ft_strrchr(args[i], '=')) != NULL)))
	{
		*arg_ptr = '\0';
		arg_ptr++;
		(void)ft_setenv(args[i], arg_ptr, 1, env);
		i++;
	}
	return (1);
}
