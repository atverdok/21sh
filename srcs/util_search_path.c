/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_search_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:45:44 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/27 17:45:50 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int			is_local_file_dir(t_pipe *pipe_node, struct stat *stat_f)
{
	char *full_path;

	if (ft_strchr(pipe_node->arg[0], '/') == NULL)
		return (0);
	if (lstat(pipe_node->arg[0], stat_f))
	{
		full_path = get_full_path_lokal(pipe_node->arg[0]);
		if (!lstat(full_path, stat_f) && stat_f->st_dev)
		{
			pipe_node->cmd_full_path = full_path;
			return (1);
		}
		ft_strdel(&full_path);
	}
	pipe_node->cmd_full_path = ft_strdup(pipe_node->arg[0]);
	return (1);
}

static char	*get_path(char *path, char *arg)
{
	char *full_path;

	full_path = ft_strnew(ft_strlen(path) + ft_strlen(arg) + 1);
	full_path = ft_strcpy(full_path, path);
	full_path = ft_strcat(full_path, "/");
	full_path = ft_strcat(full_path, arg);
	return (full_path);
}

int			is_path_file(t_pipe *pipe_node, struct stat *stat_f, char **env)
{
	char *env_path;
	char *path;
	char *full_path;

	if (env && (ft_getenv("PATH", env) != NULL))
	{
		env_path = ft_strdup(ft_getenv("PATH", env));
		path = ft_strtok_quote(env_path, ":");
		while (path != NULL)
		{
			full_path = get_path(path, pipe_node->arg[0]);
			if (lstat(full_path, stat_f))
				path = ft_strtok_quote(NULL, ":");
			else
			{
				pipe_node->cmd_full_path = full_path;
				ft_strdel(&env_path);
				return (1);
			}
			ft_strdel(&full_path);
		}
		ft_strdel(&env_path);
	}
	return (0);
}

static int	print_error_file_or_directory(char *arg)
{
	if (ft_strchr(arg, '/'))
		ft_print_error("21sh: ", arg, ERR_NSFOD);
	else
		ft_print_error("21sh: ", arg, ERR_CNF);
	return (1);
}

int			is_file_or_directory(t_pipe *pipe_node, char **env)
{
	struct stat stat_f;

	ft_bzero(&stat_f, sizeof(stat_f));
	if (!is_local_file_dir(pipe_node, &stat_f))
		is_path_file(pipe_node, &stat_f, env);
	if (stat_f.st_dev)
	{
		if ((stat_f.st_mode & S_IFMT) == S_IFDIR
				|| (stat_f.st_mode & S_IFMT) == S_IFLNK)
		{
			ft_print_error("21sh: ", pipe_node->arg[0], ERR_PD);
			return (1);
		}
		else if (((stat_f.st_mode & S_IFMT) == S_IFREG)
				&& (!(stat_f.st_mode & (1 << 0)
						|| !(stat_f.st_mode & (1 << 3)
							|| !(stat_f.st_mode & (1 << 6))))))
		{
			ft_print_error("21sh: ", pipe_node->arg[0], ERR_PD);
			return (1);
		}
		return (0);
	}
	return (print_error_file_or_directory(pipe_node->arg[0]));
}
