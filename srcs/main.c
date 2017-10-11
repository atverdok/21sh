/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 10:26:07 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:35:31 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	sighandler(int num)
{
	if (g_pid && num)
	{
		kill(g_pid, SIGSTOP);
		ft_putchar('\n');
		g_pid = 0;
	}
}

int		execute(t_pipe *pipes, char **env)
{
	if (pipes->arg[0] == NULL)
		return (1);
	else if (ft_strequ_case_insen(pipes->arg[0], "setenv"))
		return (make_setenv(pipes->arg, env));
	else if (ft_strequ_case_insen(pipes->arg[0], "unsetenv"))
		return (make_unsetenv(pipes->arg, env));
	else if (ft_strequ_case_insen(pipes->arg[0], "env"))
		return (!ft_env(pipes, env));
	else if (!ft_strcmp(pipes->arg[0], "exit"))
		return (ft_exit(pipes->arg));
	else if (ft_strequ_case_insen(pipes->arg[0], "cd"))
		return (ft_cd(pipes->arg, env));
	return (0);
}

int		handling_args(char *args_del, char **env)
{
	int		status;
	char	**args_pipe;
	t_pipe	*pipes;
	t_pipe	*cur;

	args_pipe = ft_split_del(args_del, "|");
	pipes = split_pipe(args_pipe);
	cur = pipes;
	while (cur)
	{
		if (execute(cur, env) || is_file_or_directory(cur, env))
		{
			del_t_pipe(&pipes);
			ft_memdel((void *)&args_pipe);
			return (1);
		}
		cur = cur->next;
	}
	status = handling_pipe(pipes, env);
	del_t_pipe(&pipes);
	ft_memdel((void *)&args_pipe);
	return (status);
}

void	ft_shell(char **env)
{
	char	*r_line;
	char	*line;
	char	**args_del;
	int		status;
	int		i;

	status = 1;
	while (status)
	{
		ft_putstr(ft_getenv("PROMPT", env));
		r_line = read_command(env);
		ft_putstr("\n");
		line = make_str(r_line, env);
		args_del = ft_split_del(line, ";");
		i = -1;
		while (args_del[++i])
			status = handling_args(args_del[i], env);
		ft_memdel((void *)&args_del);
		ft_strdel(&line);
		ft_strdel(&r_line);
	}
}

int		main(int argc, char **argv, char **env)
{
	char *path_minishell;

	save_attributes();
	set_input_mode();
	if (argc > 1)
	{
		ft_print_error("minishell: ", argv[1], ERR_IA);
		ft_putendl_fd("usage: ./minishell", 2);
		return (0);
	}
	env = copy_arr_str(env, BUF_ENV);
	ft_setenv("PROMPT", "$> ", 1, env);
	ft_setenv("PROMPT2", "> ", 1, env);
	if ((path_minishell = get_full_path_lokal(argv[0])) != NULL)
	{
		ft_setenv("SHELL", path_minishell, 1, env);
		ft_strdel(&path_minishell);
	}
	signal(SIGINT, sighandler);
	ft_shell(env);
	reset_input_mode();
	return (0);
}
