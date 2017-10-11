/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ft_strtok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 13:06:17 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/28 13:06:21 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static void	init(char *str, char **str_ptr, int *index, int *f_q_dq)
{
	if (str != NULL)
	{
		*str_ptr = str;
		*index = 0;
		*f_q_dq = 0;
	}
}

static int	break_tok(char *str_ptr, int *start, int *index)
{
	if (str_ptr[*start] == '\0')
	{
		*start = *index;
		(*index)--;
		return (1);
	}
	return (0);
}

static char	*return_tok(char *str_ptr, int start)
{
	if (str_ptr[start] == '\0')
		return (NULL);
	else
		return (&str_ptr[start]);
}

char		*ft_strtok_quote(char *str, char *del)
{
	static int	index = 0;
	static int	f_q_dq = 0;
	static char	*str_ptr;
	int			start;
	int			i;

	init(str, &str_ptr, &index, &f_q_dq);
	start = index;
	while (str_ptr[index] != '\0')
	{
		hangling_dquote(&f_q_dq, str_ptr[index]);
		i = -1;
		while (del[++i] != '\0')
		{
			if (str_ptr[index] == del[i] && !IS_FLAG(f_q_dq))
			{
				str_ptr[index++] = '\0';
				if (break_tok(str_ptr, &start, &index))
					break ;
				return (&str_ptr[start]);
			}
		}
		index++;
	}
	return (return_tok(str_ptr, start));
}
