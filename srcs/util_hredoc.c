/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_hredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 07:04:39 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 07:04:50 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

t_string	*read_line_heredoc_n(int prompt)
{
	t_string	*buf;
	int			c;

	buf = new_string(MAX_INPUT);
	while (1)
	{
		c = ft_get_char();
		if ((c == 4 || c == EOF) && buf->curent_size == 0)
		{
			ft_putstr("21sh: warning: here-document delimited by end-of-file");
			return (buf);
		}
		else if (c == 3)
		{
			mov_last_row(buf, prompt);
			buf->curent_size = -1;
			return (buf);
		}
		else if (c == '\t')
			ft_putchar('\a');
		else if (c == 27)
			move_cursor(&buf, prompt);
		else if (add_to_buff(&buf, c, prompt))
			return (buf);
	}
}

int			is_eof(t_string **str, char *s)
{
	if (!ft_strncmp((*str)->str, s, ft_strlen(s)) || (*str)->curent_size == 0)
	{
		del_t_string(str);
		return (1);
	}
	return (0);
}

int			ft_heredoc(char *s)
{
	t_string	*str;
	int			fd[2];

	pipe(fd);
	while (1)
	{
		ft_putstr(HEREDOC);
		str = read_line_heredoc_n((int)ft_strlen(HEREDOC));
		ft_putstr("\n");
		if (str->curent_size == -1)
		{
			del_t_string(&str);
			return (-1);
		}
		if (is_eof(&str, s))
			break ;
		write(fd[1], str->str, (str->curent_size < PIPE_BUF) ?
				(size_t)str->curent_size : PIPE_BUF);
		write(fd[1], "\n", 1);
		del_t_string(&str);
	}
	close(fd[1]);
	return (fd[0]);
}
