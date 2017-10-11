/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 04:09:12 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:09:18 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

/*
** \\ - backslash
** \a - alert (BEL)
** \b - backspace
** \c - produce no further output
** \e - escape
** \f - form feed
** \n - new line
** \r - carriage return
** \t - horizontal tab
** \v - vertical tab
*/

static void		control_charac(char **s)
{
	if (*(*s + 1) == 'a')
		ft_putchar('\a');
	else if (*(*s + 1) == 'b')
		ft_putchar('\b');
	else if (*(*s + 1) == 'f')
		ft_putchar('\f');
	else if (*(*s + 1) == 'n')
		ft_putchar('\n');
	else if (*(*s + 1) == 'r')
		ft_putchar('\r');
	else if (*(*s + 1) == 't')
		ft_putchar('\t');
	else if (*(*s + 1) == 'v')
		ft_putchar('\v');
	else if (*(*s + 1) == '|')
		ft_putchar('|');
	else
		(*s)--;
}

int				ft_putstr_control_charac(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (*s == 92 && *(s + 1) == 'c')
			{
				ft_putstr_fd("\e[7m%\e[27m", 2);
				return (1);
			}
			else if (*s == 92 && *(s + 1) == '\\')
			{
				s++;
				continue;
			}
			else if (*s == 92 && *(s + 1) && *(s - 2) != '\\')
			{
				control_charac(&s);
				s++;
			}
			else
				ft_putchar(*s);
			s++;
		}
	}
	return (0);
}

static int		parse_options(char *str, int n_e[2])
{
	while (str++ && *str != '\0')
	{
		if (*str == 'n')
			n_e[0] = 1;
		else if (*str == 'E')
			n_e[1] = 1;
		else
		{
			ft_bzero(&(*n_e), sizeof(*n_e));
			return (0);
		}
	}
	return (1);
}

void			print_end(int n)
{
	if (n)
		ft_putstr_fd("\e[7m%\e[27m", 2);
	ft_putchar('\n');
}

int				ft_echo(char **args)
{
	int		i;
	int		n_e[2];
	int		len;

	ft_bzero(&n_e, sizeof(n_e));
	i = 0;
	len = len_arr_str(args) - 1;
	while (++i <= len && args[i][0] == '-')
		if (!parse_options(args[i], n_e))
			break ;
	while (args[i] != NULL)
	{
		if (!n_e[1])
		{
			if (ft_putstr_control_charac(args[i]))
				break ;
		}
		else
			ft_putstr_fd(args[i], 1);
		if (i != len)
			ft_putchar(' ');
		i++;
	}
	print_end(n_e[0]);
	return (0);
}
