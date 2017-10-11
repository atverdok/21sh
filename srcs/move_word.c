/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 05:33:33 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 05:33:41 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	begin_word(t_string **s, int cur_pos, int c, int prompt)
{
	int new_pos;

	if ((*s)->mov->pos_column == ((*s)->curent_size) && (*s)->next)
	{
		set_cursor(cur_pos, (cur_pos + get_new_pos(*s, c, prompt)));
		(*s) = (*s)->next;
	}
	if ((*s)->mov->pos_column < (*s)->curent_size)
	{
		new_pos = (*s)->mov->pos_column + 1;
		while ((*s)->str[new_pos] == ' ' && new_pos < (*s)->curent_size)
			new_pos++;
		while ((*s)->str[new_pos + 1] != ' '
				&& new_pos < ((*s)->curent_size - 1))
			new_pos++;
		prompt = ((*s)->prev == NULL) ? prompt : 0;
		set_cursor((*s)->mov->pos_column + prompt, new_pos + prompt);
		(*s)->mov->pos_column += new_pos - (*s)->mov->pos_column;
	}
}

void	end_word(t_string **s, int cur_pos, int c, int prompt)
{
	int new_pos;

	if (!(*s)->mov->pos_column && (*s)->prev)
	{
		set_cursor(cur_pos, (cur_pos - get_new_pos(*s, c, prompt)));
		(*s) = (*s)->prev;
	}
	if ((*s)->mov->pos_column > 0)
	{
		new_pos = (*s)->mov->pos_column - 1;
		while ((*s)->str[new_pos] == ' ' && new_pos > 0)
			new_pos--;
		while ((*s)->str[new_pos - 1] != ' ' && new_pos > 0)
			new_pos--;
		prompt = ((*s)->prev == NULL) ? prompt : 0;
		set_cursor((*s)->mov->pos_column + prompt, new_pos + prompt);
		(*s)->mov->pos_column -= (*s)->mov->pos_column - new_pos;
	}
}

void	mov_word(t_string **s, int c, int *index, int prompt)
{
	int cur_pos;

	cur_pos = get_cur_pos(*s, prompt);
	if (c == KEY_RIGHT
			&& ((*s)->mov->pos_column < (*s)->curent_size || (*s)->next))
		begin_word(s, cur_pos, c, prompt);
	if (c == KEY_LEFT && cur_pos > prompt)
		end_word(s, cur_pos, c, prompt);
	*index = -1;
}
