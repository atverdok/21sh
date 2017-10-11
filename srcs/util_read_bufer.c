/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_read_bufer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:04:36 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 08:08:22 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	util_print_set(t_string **s, int prompt)
{
	char *p_str;

	ft_putstr("\e[J");
	p_str = (*s)->str;
	(*s)->str = (((*s)->str + (*s)->mov->pos_column));
	print_string(*s, prompt);
	(*s)->str = p_str;
	set_cursor(get_end_pos(*s, prompt), get_cur_pos(*s, prompt));
}

void	insert_char(t_string *s, int c, int prompt)
{
	char *p_str;

	if ((s->curent_size + 1) == (int)s->total_size)
	{
		s->str = ft_realoc(s->str, (size_t)(s->total_size + MAX_INPUT));
		s->total_size += MAX_INPUT;
	}
	ft_memmove((s->str + (s->mov->pos_column + 1)),
			(s->str + s->mov->pos_column),
			(size_t)(s->curent_size - s->mov->pos_column));
	s->str[s->mov->pos_column] = (char)c;
	s->curent_size++;
	ft_putstr("\e[J");
	p_str = s->str;
	s->str = ((s->str + s->mov->pos_column));
	print_string(s, prompt);
	s->str = p_str;
	s->mov->pos_column++;
	set_cursor(get_end_pos(s, prompt), get_cur_pos(s, prompt));
}

int		len_prompt(char **env, int f_q_dq)
{
	if (IS_QUOTE(f_q_dq))
		return ((int)ft_strlen(QUOTE));
	else if (IS_DQUOTE(f_q_dq))
		return ((int)ft_strlen(DQUOTE));
	else if (IS_BACKSLASH(f_q_dq))
		return (((ft_getenv("PROMPT2", env))
					? (int)ft_strlen(ft_getenv("PROMPT2", env))
					: 0));
	else
		return (((ft_getenv("PROMPT", env))
					? (int)ft_strlen(ft_getenv("PROMPT", env))
					: 0));
}

int		add_to_buff(t_string **s, int c, int prompt)
{
	if (ft_isprint(c) && (*s)->mov->pos_column < (*s)->curent_size &&
			c != 0x0000007f)
		insert_char(*s, c, prompt);
	else if (c == 0x0000007f && ((*s)->mov->pos_column || (*s)->prev))
		backspace(s, prompt);
	else if (ft_isprint(c) && (*s)->mov->pos_column == (*s)->curent_size
			&& c != 0x0000007f)
	{
		if ((*s)->curent_size == (int)(*s)->total_size)
		{
			(*s)->str = ft_realoc((*s)->str,
					(size_t)((*s)->total_size + MAX_INPUT));
			(*s)->total_size += MAX_INPUT;
		}
		(*s)->str[(*s)->curent_size] = (char)c;
		(*s)->curent_size++;
		(*s)->mov->pos_column++;
		ft_putchar((char)c);
		move_cursore_new_line((*s)->mov->pos_column, prompt);
	}
	else if (c == '\n')
		return (1);
	else
		ft_putchar('\a');
	return (0);
}
