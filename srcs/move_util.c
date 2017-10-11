/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 06:02:50 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 06:02:56 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	print_esc(int number, char ch)
{
	ft_putstr("\e[");
	ft_putnbr(number);
	ft_putchar(ch);
}

void	move_cursore_new_line(int pos, int prompt)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!((pos + prompt) % w.ws_col))
		ft_putstr(" \b");
}

void	set_cursor(int cur_pos, int new_pos)
{
	struct winsize	w;
	int				cur_row;
	int				new_row;
	int				cur_col;
	int				new_col;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cur_row = cur_pos / w.ws_col;
	new_row = new_pos / w.ws_col;
	cur_col = cur_pos % w.ws_col;
	new_col = new_pos % w.ws_col;
	if (new_row - cur_row)
	{
		if (new_pos > cur_pos)
			print_esc((new_row - cur_row), KEY_DOWN);
		else if (new_pos < cur_pos)
			print_esc((cur_row - new_row), KEY_UP);
	}
	if (cur_col < new_col)
		print_esc((new_col - cur_col), KEY_RIGHT);
	else if (cur_col > new_col)
		print_esc((cur_col - new_col), KEY_LEFT);
}

int		get_cur_pos(t_string *s, int prompt)
{
	struct winsize	w;
	int				cur_pos;
	int				rows;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cur_pos = s->mov->pos_column + ((s->prev == NULL) ? prompt : 0);
	while (s->prev)
	{
		s = s->prev;
		rows = ((s->curent_size + ((s->prev == NULL) ? prompt : 0))
				/ w.ws_col) + 1;
		cur_pos += rows * w.ws_col;
	}
	return (cur_pos);
}

int		get_new_pos(t_string *s, int c, int prompt)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (c == KEY_LEFT)
	{
		if (!s->mov->pos_column && s->prev)
			return (w.ws_col - ((s->prev->curent_size +
						((s->prev->prev == NULL) ? prompt : 0)) % w.ws_col));
	}
	else if (c == KEY_RIGHT)
	{
		if ((s->curent_size == s->mov->pos_column) && s->next)
			return (w.ws_col - ((s->curent_size +
							((s->prev == NULL) ? prompt : 0)) % w.ws_col));
	}
	return (1);
}
