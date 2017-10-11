/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 07:48:17 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 07:48:25 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int		hangling_dquote(int *f_q_dq, int c)
{
	if (c == '"' && !IS_QUOTE(*f_q_dq))
	{
		*f_q_dq = (*f_q_dq ^ (1 << 2));
		*f_q_dq = (*f_q_dq ^ (1 << 0));
		return (1);
	}
	else if (c == '\'' && !IS_DQUOTE(*f_q_dq))
	{
		*f_q_dq = (*f_q_dq ^ (1 << 1));
		*f_q_dq = (*f_q_dq ^ (1 << 0));
		return (1);
	}
	return (0);
}

void	print_dquote(int *f_q_dq, char **env)
{
	if (IS_FLAG(*f_q_dq))
	{
		ft_putchar('\n');
		if (IS_QUOTE(*f_q_dq))
			ft_putstr(QUOTE);
		else if (IS_DQUOTE(*f_q_dq))
			ft_putstr(DQUOTE);
		else if (IS_BACKSLASH(*f_q_dq))
		{
			if (ft_getenv("PROMPT2", env))
				ft_putstr(ft_getenv("PROMPT2", env));
			*f_q_dq = (*f_q_dq ^ (1 << 4));
			*f_q_dq = (*f_q_dq ^ (1 << 0));
		}
	}
}

void	search_quote(char *str, int *f_q_dq)
{
	while (*str)
	{
		if (*str == '\\' && *(str - 1) != '\\'
				&& *(str + 1) == '\n' && *(str + 2) == '\0'
				&& !IS_FLAG(*f_q_dq))
		{
			*f_q_dq = (*f_q_dq ^ (1 << 4));
			*f_q_dq = (*f_q_dq ^ (1 << 0));
			str++;
		}
		else
			(void)hangling_dquote(f_q_dq, *str);
		str++;
	}
}
