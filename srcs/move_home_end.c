/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_home_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 05:46:50 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 05:46:59 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	home(t_string **s, int *index, int prompt)
{
	int cur_pos;

	cur_pos = get_cur_pos(*s, prompt);
	if ((*s)->mov->pos_column > 0)
		set_cursor(cur_pos, (cur_pos - (*s)->mov->pos_column));
	else if ((*s)->prev)
	{
		(*s) = (*s)->prev;
		set_cursor(cur_pos, (get_cur_pos(*s, prompt) - (*s)->curent_size));
	}
	(*s)->mov->pos_column = 0;
	*index = -1;
}

void	end(t_string **s, int *index, int prompt)
{
	int cur_pos;

	cur_pos = get_cur_pos(*s, prompt);
	if ((*s)->mov->pos_column < (*s)->curent_size)
		set_cursor(cur_pos,
				(cur_pos + ((*s)->curent_size - (*s)->mov->pos_column)));
	else if ((*s)->next)
	{
		(*s) = (*s)->next;
		set_cursor(cur_pos, (get_cur_pos(*s, prompt) + (*s)->curent_size));
	}
	(*s)->mov->pos_column = (*s)->curent_size;
	*index = -1;
}

void	home_global(t_string **s, int cur_pos, int prompt)
{
	set_cursor(cur_pos, prompt);
	while ((*s)->prev)
	{
		(*s)->mov->pos_column = 0;
		(*s) = (*s)->prev;
	}
	(*s)->mov->pos_column = 0;
}

void	end_global(t_string **s, int cur_pos, int prompt)
{
	int new_pos;

	while ((*s)->next)
	{
		(*s)->mov->pos_column = (*s)->curent_size;
		(*s) = (*s)->next;
	}
	(*s)->mov->pos_column = (*s)->curent_size;
	new_pos = get_cur_pos(*s, prompt);
	set_cursor(cur_pos, new_pos);
}

void	move_home_end(t_string **s, int c, int *index, int prompt)
{
	int cur_pos;

	cur_pos = get_cur_pos(*s, prompt);
	if (c == KEY_HOME && cur_pos > prompt)
		home_global(s, cur_pos, prompt);
	else if (c == KEY_END &&
			(((*s)->mov->pos_column < (*s)->curent_size) || (*s)->next))
		end_global(s, cur_pos, prompt);
	*index = -1;
}
