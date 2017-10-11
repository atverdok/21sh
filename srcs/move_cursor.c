/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:00:29 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 05:17:56 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int		get_end_pos(t_string *s, int prompt)
{
	int new_pos;

	while (s->next)
		s = s->next;
	new_pos = s->curent_size - s->mov->pos_column;
	new_pos += get_cur_pos(s, prompt);
	return (new_pos);
}

void	move_left_right(t_string **s, int c, int *index, int prompt)
{
	int cur_pos;

	cur_pos = get_cur_pos(*s, prompt);
	if (c == KEY_LEFT && cur_pos > prompt)
	{
		set_cursor(cur_pos, (cur_pos - get_new_pos(*s, c, prompt)));
		if (!(*s)->mov->pos_column)
			(*s) = (*s)->prev;
		else
			(*s)->mov->pos_column--;
	}
	else if (c == KEY_RIGHT)
	{
		if ((*s)->mov->pos_column < (*s)->curent_size || (*s)->next)
		{
			set_cursor(cur_pos, (cur_pos + get_new_pos(*s, c, prompt)));
			if (((*s)->curent_size == (*s)->mov->pos_column) && (*s)->next)
				(*s) = (*s)->next;
			else
				(*s)->mov->pos_column++;
		}
	}
	*index = -1;
}

void	mov_last_row(t_string *s, int prompt)
{
	struct winsize	w;
	int				cur_row;
	int				total_row;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cur_row = get_cur_pos(s, prompt);
	while (s->next)
		s = s->next;
	s->mov->pos_column = s->curent_size;
	total_row = get_cur_pos(s, prompt);
	set_cursor(cur_row, (total_row - ((s->prev == NULL) ? 0 : prompt)));
}

void	function_keys(t_string **s, int *index, int prompt)
{
	int c;

	ft_get_char();
	ft_get_char();
	c = ft_get_char();
	if (c == KEY_RIGHT || c == KEY_LEFT)
		mov_word(s, c, index, prompt);
	else if (c == KEY_HOME || c == KEY_END)
		move_home_end(s, c, index, prompt);
}

void	move_cursor(t_string **s, int prompt)
{
	int			c;
	static int	index = -1;

	ft_get_char();
	c = ft_get_char();
	if (c == 49)
		function_keys(s, &index, prompt);
	else if (c == KEY_HOME)
		home(s, &index, prompt);
	else if (c == KEY_END)
		end(s, &index, prompt);
	else if (c == KEY_LEFT || c == KEY_RIGHT)
		move_left_right(s, c, &index, prompt);
	else if (c == KEY_UP || c == KEY_DOWN)
		move_up_down(s, c, &index, prompt);
	else if (c == KEY_DELETE)
		delete_char(s, &index, prompt);
}
