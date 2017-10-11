/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:43:41 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/27 17:43:49 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	ft_print_error(char *name, char *arg, int code)
{
	ft_putstr_fd(name, 2);
	if (code == ERR_PD)
		ft_putstr_fd("permission denied: ", 2);
	else if (code == ERR_NSFOD)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (code == ERR_NAD)
		ft_putstr_fd("not a directory: ", 2);
	else if (code == ERR_CNF)
		ft_putstr_fd("command not found: ", 2);
	else if (code == ERR_SNIPWD)
		ft_putstr_fd("string not in pwd: ", 2);
	else if (code == ERR_TMA)
		ft_putstr_fd("too many arguments ", 2);
	else if (code == ERR_NVITC)
		ft_putstr_fd("not valid in this context: ", 2);
	else if (code == ERR_IA)
		ft_putstr_fd("invalid argument: ", 2);
	else if (code == ERR_ERROR)
		ft_putstr_fd("error", 2);
	else if (code == ERR_ILLOP)
		ft_putstr_fd("illegal option ", 2);
	else if (code == ERR_PE)
		ft_putstr_fd("parse error ", 2);
	ft_putendl_fd(arg, 2);
}

void	error_redir(t_pipe *new_pipe, int i)
{
	ft_print_error("sh21: ", new_pipe->arg[i + 1], ERR_PE);
	ft_memmove(&new_pipe->arg[i], &new_pipe->arg[i + 1],
			(len_arr_str(new_pipe->arg) - i) * sizeof(char *));
	new_pipe->fd_in = -1;
}
