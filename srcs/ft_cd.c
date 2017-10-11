/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 04:08:41 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:08:47 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char	*make_pwd(char **args, char *old_pwd, char **env)
{
	char	*pwd;
	char	*home;

	home = ft_getenv("HOME", env);
	if (home && len_arr_str(args) == 1)
		pwd = ft_strdup(home);
	else if (home && !(ft_strncmp(args[1], "~", 1)))
	{
		pwd = ft_strnew(ft_strlen((args[1] + 1)) + ft_strlen(home));
		pwd = ft_strncpy(pwd, home, ft_strlen(home));
		pwd = ft_strcat(pwd, (args[1] + 1));
	}
	else if (args[1] && !ft_strcmp(args[1], "-"))
		pwd = ft_strdup(old_pwd);
	else if (args[1])
		pwd = ft_strdup(args[1]);
	else
		pwd = get_pwd();
	return (pwd);
}

int		make_chdir(char **pwd)
{
	struct stat	stat_f;

	if (chdir(*pwd) != 0)
	{
		if (lstat(*pwd, &stat_f))
			ft_print_error("ft_cd: ", *pwd, ERR_NSFOD);
		else if (((stat_f.st_mode & S_IFMT) != S_IFDIR)
				&& ((stat_f.st_mode & S_IFMT) != S_IFLNK))
			ft_print_error("ft_cd: ", *pwd, ERR_NAD);
		else if (!(stat_f.st_mode & (1 << 2)))
			ft_print_error("ft_cd: ", *pwd, ERR_PD);
		ft_strdel(pwd);
		return (0);
	}
	return (1);
}

void	print_replase_pwd(char **args, char *pwd, char **env)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (args[1] && !ft_strcmp(args[1], "-"))
	{
		if (home && pwd && !(ft_strncmp(pwd, home, ft_strlen(home))))
		{
			pwd[0] = '~';
			ft_memmove((pwd + 1), (pwd + ft_strlen(home)), ft_strlen(pwd));
		}
		ft_putstr(pwd);
		ft_putchar('\n');
	}
}

void	set_pwd_oldpwd(char *old_pwd, char **env)
{
	char *pwd;

	pwd = get_pwd();
	ft_setenv("PWD", pwd, 1, env);
	ft_strdel(&pwd);
	ft_setenv("OLDPWD", old_pwd, 1, env);
}

int		ft_cd(char **args, char **env)
{
	char		*pwd;
	char		*old_pwd;
	static char	*old_pwd1 = NULL;

	if (old_pwd1 == NULL)
		old_pwd1 = get_pwd();
	if (len_arr_str(args) == 3)
		ft_print_error("ft_cd: ", args[1], ERR_SNIPWD);
	else if (len_arr_str(args) > 3)
		ft_print_error("ft_cd: ", "", ERR_TMA);
	else
	{
		pwd = make_pwd(args, old_pwd1, env);
		old_pwd = get_pwd();
		if (make_chdir(&pwd))
		{
			ft_strdel(&old_pwd1);
			old_pwd1 = ft_strdup(old_pwd);
			set_pwd_oldpwd(old_pwd1, env);
			print_replase_pwd(args, pwd, env);
		}
		ft_strdel(&old_pwd);
		ft_strdel(&pwd);
	}
	return (1);
}
