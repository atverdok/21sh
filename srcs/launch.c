/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:58:30 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:32:14 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	make_execve(t_pipe *current, char **env)
{
	if (ft_strequ_case_insen(current->arg[0], "echo"))
	{
		ft_echo(current->arg);
		exit(0);
	}
	else
		execve(current->cmd_full_path, current->arg, env);
}

void	make_redir(t_pipe *current)
{
	if (current->fd_out)
		dup2(current->fd_out, 1);
	if (current->fd_in)
		dup2(current->fd_in, 0);
	if (current->fd_err == -1)
		close(2);
	else if (current->fd_err)
		dup2(current->fd_err, 2);
}

t_pipe	*make_pipe(t_pipe *pipe_node, char **env)
{
	int		pd[2];
	t_pipe	*current;

	current = pipe_node;
	while (current->next)
	{
		pipe(pd);
		if (!fork())
		{
			dup2(pd[1], 1);
			make_redir(current);
			make_execve(current, env);
		}
		else
		{
			wait(NULL);
			dup2(pd[0], 0);
			close(pd[1]);
			close(pd[0]);
			current = current->next;
		}
	}
	return (current);
}

int		handling_pipe(t_pipe *pipe_node, char **env)
{
	int		status;
	t_pipe	*current;

	reset_input_mode();
	g_pid = fork();
	if (g_pid == 0)
	{
		current = make_pipe(pipe_node, env);
		make_redir(current);
		make_execve(current, env);
	}
	else if (g_pid < 0)
		ft_print_error("sh21: ", "Error forking", ERR_ERROR);
	else
		waitpid(g_pid, &status, 0);
	set_input_mode();
	g_pid = 0;
	return (1);
}

t_pipe	*split_pipe(char **args_pipe)
{
	char	**args;
	int		i;
	t_pipe	*pipes;
	t_pipe	*new_pipe;

	i = -1;
	pipes = NULL;
	while (args_pipe[++i] != NULL)
	{
		args = ft_split_del(args_pipe[i], DELIM);
		new_pipe = create_t_pipe();
		new_pipe->arg = delite_q(args);
		check_redirections(new_pipe);
		if (new_pipe->fd_in == -1)
		{
			del_t_pipe(&new_pipe);
			break ;
		}
		add_list_t_pipe(&pipes, new_pipe);
	}
	return (pipes);
}
