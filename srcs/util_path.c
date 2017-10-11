/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 13:27:43 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/28 13:27:48 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char	*get_pwd(void)
{
	char *pwd;
	char buff[MAXPATHLEN];

	pwd = NULL;
	if (getcwd(buff, MAXPATHLEN) == NULL)
		ft_print_error("get_pwd: ", "", ERR_ERROR);
	else
		pwd = ft_strdup(buff);
	return (pwd);
}

char	*get_full_path_lokal(char *str)
{
	char *full_path;
	char *pwd;
	char *str_ptr;

	if ((pwd = get_pwd()) != NULL)
	{
		full_path = pwd;
		if ((str_ptr = ft_strrchr(str, '/')) != NULL)
		{
			full_path = ft_strnew(ft_strlen(pwd) + ft_strlen(str_ptr));
			full_path = ft_strncpy(full_path, pwd, ft_strlen(pwd));
			full_path = ft_strcat(full_path, str_ptr);
			ft_strdel(&pwd);
		}
		return (full_path);
	}
	return (NULL);
}

char	**delite_q(char **args)
{
	int		f_q_dq;
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (args && args[i])
	{
		f_q_dq = 0;
		ptr = args[i];
		j = 0;
		while (ptr && ptr[j] != '\0')
		{
			if ((ptr[j] == '"' || ptr[j] == '\'')
				&& hangling_dquote(&f_q_dq, ptr[j]))
			{
				ft_memmove((ptr + j), (ptr + j + 1), ft_strlen((ptr + j)));
				continue ;
			}
			j++;
		}
		i++;
	}
	return (args);
}
