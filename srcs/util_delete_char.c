/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_delete_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 11:40:10 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 11:40:17 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	delete_cur_row(t_string **s)
{
	ft_memmove(((*s)->str + (*s)->mov->pos_column),
			((*s)->str + ((*s)->mov->pos_column + 1)),
			(size_t)((*s)->curent_size - (*s)->mov->pos_column));
	(*s)->curent_size--;
	(*s)->str[(*s)->curent_size] = '\0';
}

void	delete_char(t_string **s, int *index, int prompt)
{
	t_string *ptr_s;

	ft_get_char();
	if (((*s)->mov->pos_column + 1) <= (*s)->curent_size)
		delete_cur_row(s);
	else if ((*s)->next)
	{
		if (((*s)->curent_size + (*s)->next->curent_size) >=
				(int)(*s)->total_size)
		{
			(*s)->str = ft_realoc((*s)->str,
					(size_t)((*s)->total_size + (*s)->next->curent_size));
			(*s)->total_size += (*s)->next->curent_size;
		}
		ptr_s = (*s)->next->next;
		ft_memcpy(((*s)->str + (*s)->curent_size), (*s)->next->str,
				(size_t)(*s)->next->curent_size);
		(*s)->curent_size += (*s)->next->curent_size;
		if ((*s)->next->next)
			(*s)->next->next->prev = *s;
		del_t_string(&(*s)->next);
		(*s)->next = ptr_s;
	}
	util_print_set(s, prompt);
	*index = -1;
}
