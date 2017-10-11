/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_backspace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 11:44:26 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 11:44:32 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	backspace_cur_row(t_string **s)
{
	ft_memmove(((*s)->str + ((*s)->mov->pos_column - 1)),
			((*s)->str + (*s)->mov->pos_column),
			(size_t)((*s)->curent_size - (*s)->mov->pos_column));
	(*s)->curent_size--;
	(*s)->str[(*s)->curent_size] = '\0';
	(*s)->mov->pos_column--;
}

void	realoc_string(t_string **s)
{
	if (((*s)->curent_size + (*s)->prev->curent_size) >=
			(int)(*s)->prev->total_size)
	{
		(*s)->prev->str = ft_realoc((*s)->prev->str,
					(size_t)((*s)->prev->total_size + (*s)->curent_size));
		(*s)->prev->total_size += (*s)->curent_size;
	}
}

void	backspace(t_string **s, int prompt)
{
	t_string	*ptr_s;
	int			cur_pos;

	cur_pos = get_cur_pos(*s, prompt);
	if (((*s)->mov->pos_column - 1) >= 0)
		backspace_cur_row(s);
	else if ((*s)->prev)
	{
		realoc_string(s);
		ptr_s = (*s)->prev;
		ft_memcpy(((*s)->prev->str + (*s)->prev->curent_size), (*s)->str,
				(size_t)(*s)->curent_size);
		(*s)->prev->curent_size += (*s)->curent_size;
		(*s)->prev->next = (*s)->next;
		if ((*s)->next)
			(*s)->next->prev = (*s)->prev;
		del_t_string(s);
		*s = ptr_s;
	}
	set_cursor(cur_pos, get_cur_pos(*s, prompt));
	util_print_set(s, prompt);
}
