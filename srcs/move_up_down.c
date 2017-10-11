/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 05:59:46 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 05:59:52 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	move_up(t_string **s, int cur_pos, int *index, int prompt)
{
	int	tmp;

	if ((*s)->mov->pos_column == (*s)->curent_size && (*index) == -1)
	{
		tmp = (*s)->mov->pos_column +
			((*s)->prev->curent_size - (*s)->prev->mov->pos_column);
		(*s)->mov->pos_column = 0;
		tmp += get_new_pos(*s, KEY_LEFT, prompt);
	}
	else
	{
		tmp = (*index > 0) ? *index : (*s)->mov->pos_column;
		(*s)->prev->mov->pos_column = (((*s)->prev->curent_size < tmp)
				? (*s)->prev->curent_size : tmp);
		if ((*s)->prev->curent_size <= tmp
				&& *index < (*s)->mov->pos_column)
			*index = (*s)->mov->pos_column;
		tmp = (*s)->mov->pos_column +
			((*s)->prev->curent_size - (*s)->prev->mov->pos_column);
		(*s)->mov->pos_column = 0;
		tmp += get_new_pos(*s, KEY_LEFT, prompt);
	}
	set_cursor(cur_pos, (cur_pos - tmp));
	(*s) = (*s)->prev;
}

void	move_down(t_string **s, int cur_pos, int *index, int prompt)
{
	int	tmp;

	if ((*s)->mov->pos_column == (*s)->curent_size && (*index) == -1)
	{
		(*s)->next->mov->pos_column = (*s)->next->curent_size;
		tmp = (*s)->next->curent_size;
		tmp += get_new_pos(*s, KEY_RIGHT, prompt);
	}
	else
	{
		tmp = (*index > 0) ? *index : (*s)->mov->pos_column;
		(*s)->next->mov->pos_column = (((*s)->next->curent_size < tmp)
				? (*s)->next->curent_size : tmp);
		if ((*s)->next->curent_size <= tmp
				&& *index < (*s)->mov->pos_column)
			*index = (*s)->mov->pos_column;
		tmp = ((*s)->curent_size - (*s)->mov->pos_column)
			+ (*s)->next->mov->pos_column;
		(*s)->mov->pos_column = (*s)->curent_size;
		tmp += get_new_pos(*s, KEY_RIGHT, prompt);
	}
	set_cursor(cur_pos, (cur_pos + tmp));
	(*s) = (*s)->next;
}

void	move_up_down(t_string **s, int c, int *index, int prompt)
{
	struct winsize	w;
	int				cur_pos;
	t_string		*p_history;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cur_pos = get_cur_pos(*s, prompt);
	if (c == KEY_UP && (*s)->prev != NULL)
		move_up(s, cur_pos, index, prompt);
	else if (c == KEY_DOWN && (*s)->next != NULL)
		move_down(s, cur_pos, index, prompt);
	else if ((c == KEY_DOWN || c == KEY_UP)
			&& (p_history = history(*s, c)) != NULL)
	{
		move_home_end(s, KEY_HOME, index, prompt);
		ft_putstr("\e[J");
		copy_string(*s, p_history);
		print_string(*s, prompt);
		while ((*s)->next)
			(*s) = (*s)->next;
	}
}
