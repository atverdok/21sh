/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:59:53 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:26:42 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int			add_to_history(t_string ***history_buf, t_string *buf, int *i,
		int key)
{
	if (key != 1 && *i < 1)
	{
		if (*(*history_buf) != NULL)
			del_t_string((*history_buf));
		*(*history_buf) = buf;
	}
	else
	{
		if (*(*history_buf + 29) != NULL)
			del_t_string(((*history_buf) + 29));
		if (*(*history_buf + 1) != NULL)
			ft_memmove(((*history_buf) + 2), ((*history_buf) + 1),
					(28 * sizeof(t_string *)));
		*(*history_buf + 1) = buf;
		*i = 0;
	}
	return (1);
}

void		init_tmp_buf(t_string ***history_buf, t_string *buf, int key,
		int *i)
{
	t_string *tmp_buf;

	tmp_buf = new_string(buf->total_size);
	copy_string(tmp_buf, buf);
	add_to_history(history_buf, tmp_buf, i, key);
}

t_string	*history(t_string *buf, int key)
{
	static t_string	**history_buf = NULL;
	int				len;
	static int		i = 0;

	while (buf->prev)
		buf = buf->prev;
	if (history_buf == NULL)
		history_buf = ft_memalloc(sizeof(t_string *) * 30);
	if (i < 1 && key != 1)
		init_tmp_buf(&history_buf, buf, key, &i);
	len = len_arr_string(history_buf);
	if (key == 1 && buf->curent_size &&
			add_to_history(&history_buf, buf, &i, key))
		return (buf);
	if (key == KEY_UP && i < (len - 1) && i < 29)
		i++;
	else if (key == KEY_DOWN && i > 0)
		i--;
	else if ((key == KEY_UP && i == (len - 1)) || (key == KEY_DOWN && i == 0))
		return (NULL);
	return (history_buf[i]);
}
