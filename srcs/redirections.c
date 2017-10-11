/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 06:55:07 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 06:55:14 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	check_in_append(t_pipe *new_pipe, int i)
{
	if (new_pipe->fd_in)
		close(new_pipe->fd_in);
	new_pipe->fd_in = ft_heredoc(new_pipe->arg[i + 1]);
	ft_memmove(&new_pipe->arg[i], &new_pipe->arg[i + 2],
			(len_arr_str(new_pipe->arg) - (i + 1)) * sizeof(char *));
}

int		check_in(t_pipe *new_pipe, int i)
{
	int fd;

	if (ft_strcmp(new_pipe->arg[i], "<") == 0 && new_pipe->arg[i + 1])
	{
		if (new_pipe->fd_in)
			close(new_pipe->fd_in);
		if ((fd = open(new_pipe->arg[i + 1], O_RDONLY)) < 0)
		{
			ft_print_error("sh21: ", new_pipe->arg[i + 1], ERR_NSFOD);
			new_pipe->fd_in = -1;
		}
		new_pipe->fd_in = fd;
		ft_memmove(&new_pipe->arg[i], &new_pipe->arg[i + 2],
				(len_arr_str(new_pipe->arg) - (i + 1)) * sizeof(char *));
	}
	else if (ft_strcmp(new_pipe->arg[i], "<<") == 0 && new_pipe->arg[i + 1])
		check_in_append(new_pipe, i);
	else
		error_redir(new_pipe, i);
	return (1);
}

int		check_out(t_pipe *new_pipe, int i)
{
	int fd;

	if (new_pipe->arg[i + 1])
	{
		if (new_pipe->fd_out)
			close(new_pipe->fd_out);
		if (ft_strcmp(new_pipe->arg[i], ">>") == 0)
			fd = open(new_pipe->arg[i + 1],
					O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IRGRP | S_IWGRP |
					S_IWUSR);
		else
			fd = open(new_pipe->arg[i + 1],
					O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IRGRP | S_IWGRP |
					S_IWUSR);
		new_pipe->fd_out = fd;
		ft_memmove(&new_pipe->arg[i], &new_pipe->arg[i + 2],
				(len_arr_str(new_pipe->arg) - (i + 1)) *
				sizeof(char *));
	}
	else
		error_redir(new_pipe, i);
	return (1);
}

int		check_fda(t_pipe *new_pipe, char *tmp, int i)
{
	if (*(tmp + 2) == '1' || *(tmp + 2) == '2' || *(tmp + 2) == '-')
	{
		if (*(tmp - 1) == '2' && *(tmp + 2) == '-')
			new_pipe->fd_err = -1;
		else if (*(tmp - 1) == '2')
			new_pipe->fd_err = ft_atoi((tmp + 2));
		else if (*(tmp - 1) == '1' && *(tmp + 2) != '-')
			new_pipe->fd_out = ft_atoi((tmp + 2));
		else
		{
			error_redir(new_pipe, i);
			return (1);
		}
	}
	else
	{
		ft_print_error("sh21: ", (tmp + 2), ERR_ERROR);
		new_pipe->fd_in = -1;
	}
	ft_memmove(&new_pipe->arg[i], &new_pipe->arg[i + 1],
			(len_arr_str(new_pipe->arg) - i) * sizeof(char *));
	return (1);
}

void	check_redirections(t_pipe *new_pipe)
{
	int		i;
	char	*tmp;

	i = 1;
	while (new_pipe->arg && new_pipe->arg[i])
	{
		if ((tmp = ft_strstr(new_pipe->arg[i], ">&"))
				&& check_fda(new_pipe, tmp, i))
			continue ;
		else if (ft_strncmp(new_pipe->arg[i], ">", 1) == 0
				&& check_out(new_pipe, i))
			continue ;
		else if (ft_strncmp(new_pipe->arg[i], "<", 1) == 0
				&& check_in(new_pipe, i))
			continue ;
		i++;
	}
}
