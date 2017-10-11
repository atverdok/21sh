/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:04:07 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 07:49:42 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char	*only_str(t_string *head)
{
	t_string	*cur;
	int			size;
	char		*str;

	cur = head;
	size = cur->curent_size;
	while (cur->next)
	{
		size++;
		cur = cur->next;
		size += cur->curent_size;
	}
	str = ft_strnew((size_t)size);
	ft_memcpy(str, head->str, (size_t)head->curent_size);
	size = head->curent_size;
	while (head->next != NULL)
	{
		ft_memcpy((str + size), "\n", 1);
		size++;
		head = head->next;
		ft_memcpy((str + size), head->str, (size_t)head->curent_size);
		size += head->curent_size;
	}
	return (str);
}

void	print_string(t_string *tail, int prompt)
{
	while (tail->next)
	{
		ft_putstr(tail->str);
		move_cursore_new_line(tail->curent_size, ((tail->prev == NULL) ?
					prompt : 0));
		ft_putstr("\n");
		tail = tail->next;
	}
	ft_putstr(tail->str);
	move_cursore_new_line(tail->curent_size, ((tail->prev == NULL) ?
				prompt : 0));
}

int		ft_get_char(void)
{
	static int	ch;
	ssize_t		len;

	len = read(0, &ch, 1);
	if (!len)
		return (EOF);
	else
		return (ch);
}
