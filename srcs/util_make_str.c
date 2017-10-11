/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_make_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:44:25 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/27 17:44:29 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char			*q(char *str, char *str1)
{
	char *tmp;

	tmp = ft_strnew(ft_strlen(str) + ft_strlen(str1) + 1);
	ft_memcpy(tmp, str, ft_strlen(str));
	ft_strcat(tmp, str1);
	if (str != NULL)
		ft_strdel(&str);
	return (tmp);
}

void			move_char(char **str_ptr)
{
	ft_memmove(*str_ptr, (*str_ptr + 1), ft_strlen(*str_ptr));
	(*str_ptr)--;
}

void			replace_key(char **str, char **str_ptr, char **row, char **env)
{
	(*str_ptr)[0] = '\0';
	(*str_ptr)++;
	*row = q(*row, *str);
	*row = q(*row, get_value_env(str_ptr, env));
	*str = *str_ptr;
	(*str_ptr)--;
}

void			replace_tild(char **str, char **str_ptr, char **row, char **env)
{
	char *home;

	home = ft_getenv("HOME", env);
	(*str_ptr)[0] = '\0';
	(*str_ptr)++;
	*row = q(*row, *str);
	if (home)
		*row = q(*row, home);
	*str = *str_ptr;
	(*str_ptr)--;
}

char			*make_str(char *str, char **env)
{
	char	*str_ptr;
	char	*row;
	int		f_q_dq;

	f_q_dq = 0;
	str_ptr = str;
	row = ft_memalloc(1);
	while (*str_ptr != '\0')
	{
		if (*str_ptr == '"' || *str_ptr == '\'')
			hangling_dquote(&f_q_dq, *str_ptr);
		else if (*str_ptr == '\\' && *(str_ptr + 1) != '\\' && f_q_dq == 0)
			move_char(&str_ptr);
		else if (*str_ptr == '$' && *(str_ptr - 1) != '\\' && !IS_QUOTE(f_q_dq))
			replace_key(&str, &str_ptr, &row, env);
		else if (*str_ptr == '~' && *(str_ptr - 1) != '\\' && !IS_FLAG(f_q_dq))
			replace_tild(&str, &str_ptr, &row, env);
		str_ptr++;
	}
	if (ft_strlen(str) > 0)
		row = q(row, str);
	return (row);
}
