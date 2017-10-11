/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:48:45 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 06:31:31 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void		hand_ctr_d(char *buf)
{
	if (!ft_strlen(buf))
	{
		ft_putendl("exit");
		reset_input_mode();
		exit(1);
	}
	else
		ft_putchar('\a');
}

t_string	*read_line_n(int prompt)
{
	int			c;
	t_string	*string;

	string = new_string(MAX_INPUT);
	while (1)
	{
		c = ft_get_char();
		if (c == 4 || c == EOF)
			hand_ctr_d(string->str);
		else if (c == 3)
		{
			mov_last_row(string, prompt);
			ft_bzero(string->str, sizeof(char) * string->curent_size);
			string->curent_size = -1;
			return (string);
		}
		else if (c == '\t')
			ft_putchar('\a');
		else if (c == 27)
			move_cursor(&string, prompt);
		else if (add_to_buff(&string, c, prompt))
			return (string);
	}
}

void		make_command(t_string **command, t_string *str, int *f_q_dq)
{
	t_string	*cur_str;

	cur_str = str;
	while (cur_str->prev)
		cur_str = cur_str->prev;
	while (cur_str->next)
	{
		search_quote(cur_str->str, f_q_dq);
		cur_str = cur_str->next;
	}
	search_quote(cur_str->str, f_q_dq);
	while (cur_str->prev)
		cur_str = cur_str->prev;
	insert_d_list(command, cur_str);
}

char		*make_command_str(t_string *command, t_string **str)
{
	char *str_com;

	if (command && command->curent_size > 0)
		str_com = only_str(history(command, 1));
	else
	{
		str_com = ft_strdup("\0");
		if (*str)
			del_t_string(str);
	}
	return (str_com);
}

char		*read_command(char **env)
{
	int			f_q_dq;
	int			prompt;
	t_string	*command;
	t_string	*str;

	command = NULL;
	f_q_dq = 0;
	while (1)
	{
		prompt = len_prompt(env, f_q_dq);
		str = read_line_n(prompt);
		if (str->curent_size == -1)
		{
			if (command)
				del_string_command(&command);
			del_string_command(&str);
			break ;
		}
		make_command(&command, str, &f_q_dq);
		mov_last_row(command, prompt);
		if (!f_q_dq)
			break ;
		print_dquote(&f_q_dq, env);
	}
	return (make_command_str(command, &str));
}
