/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_struct_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 08:28:08 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 08:28:16 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void		copy_string(t_string *dest, t_string *s)
{
	while (s)
	{
		if (dest->curent_size > s->curent_size)
			ft_memset((dest->str + s->curent_size), 0,
					(size_t)(dest->curent_size - s->curent_size));
		if ((dest->curent_size + s->curent_size) >= (int)dest->total_size)
		{
			dest->str = ft_realoc(dest->str,
					(size_t)(dest->total_size + s->curent_size));
			dest->total_size += s->curent_size;
		}
		ft_memcpy(dest->str, s->str, (size_t)s->curent_size);
		dest->curent_size = s->curent_size;
		dest->total_size = s->total_size;
		dest->mov->pos_column = s->curent_size;
		if (s->next == NULL && dest->next != NULL)
			del_string_wish_cur_pos(&dest->next);
		else if (s->next != NULL && dest->next == NULL)
		{
			dest->next = new_string(s->total_size);
			dest->next->prev = dest;
		}
		s = s->next;
		dest = dest->next;
	}
}

void		del_t_string(t_string **string)
{
	ft_strdel(&(*string)->str);
	ft_memdel((void *)&(*string)->mov);
	ft_memdel((void *)string);
}

void		del_string_wish_cur_pos(t_string **string)
{
	t_string *cur;

	while (*string)
	{
		cur = *string;
		(*string) = (*string)->next;
		del_t_string(&(cur));
	}
}

void		del_string_command(t_string **string)
{
	t_string *cur;

	while ((*string)->prev)
		(*string) = (*string)->prev;
	while (*string)
	{
		cur = *string;
		(*string) = (*string)->next;
		del_t_string(&(cur));
	}
}

t_string	*new_string(size_t size)
{
	t_string *string;

	string = ft_memalloc(sizeof(t_string));
	string->total_size = size;
	string->str = ft_memalloc(sizeof(char) * (size + 1));
	string->mov = ft_memalloc(sizeof(t_mov));
	return (string);
}
