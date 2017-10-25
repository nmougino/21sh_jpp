/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:22:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/25 14:01:14 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** i = 0 => nothing
** i = -1 => L (defaut)
** i = 1 => P
*/

static int	check_options(char *com)
{
	int	i;

	i = 0;
	if (!com)
		return (0);
	if (com[0] == '-')
	{
		++com;
		while (*com)
		{
			if (*com == 'L')
				i = 1;
			else if (*com == 'P')
				i = -1;
			else
				return (0);
			++com;
		}
	}
	return (i);
}

static int	bi_cd_err(char *tar)
{
	struct stat	buf;

	if (lstat(tar, &buf))
		ft_dprintf(2, "cd: no such file or directory: %s\n", tar);
	else if (!S_ISDIR(buf.st_mode))
		ft_dprintf(2, "cd: not a directory: %s\n", tar);
	else if (access(tar, F_OK))
		ft_dprintf(2, "cd: file is not accessible: %s\n", tar);
	else if (access(tar, X_OK))
		ft_dprintf(2, "cd: permission denied: %s\n", tar);
	else
		ft_dprintf(2, "cd: unknow error: %s\n", tar);
	return (-1);
}

static int	do_chdir(char *curpath, int op)
{
	int		ans;
	char	*tmp;

	ans = 0;
	tmp = getcwd(NULL, 0);
	if (chdir(curpath))
		ans = bi_cd_err(curpath);
	else if (op)
	{
		env_set("OLDPWD", tmp ? tmp : "");
		env_set("PWD", curpath ? curpath : ".");
	}
	else
	{
		env_set("OLDPWD", tmp ? tmp : "");
		ft_strdel(&tmp);
		tmp = getcwd(NULL, 0);
		env_set("PWD", tmp ? tmp : ".");
	}
	ft_strdel(&curpath);
	ft_strdel(&tmp);
	return (ans);
}

static char	*get_curpath(char **com, char **env)
{
	char	*pwd;
	char	*curpath;
	char	*tmp;

	pwd = is_env_local(env, "PWD") ? ft_strdup(get_env_local(env, "PWD"))
		: getcwd(NULL, 0);
	if (!com[1])
		curpath = ft_strdup(get_env_local(env, "HOME"));
	else
		curpath = ft_strdup(ft_strequ(com[1], "-")
		? get_env_local(env, "OLDPWD") : com[1]);
	if (curpath[0] != '/')
	{
		tmp = curpath;
		curpath = NULL;
		if (pwd)
			curpath = pwd[ft_strlen(pwd) - 1] == '/' ? ft_strdup(pwd) :
				ft_strjoin(pwd, "/");
		curpath = curpath ? ft_stradd(&curpath, tmp) : ft_strdup(tmp);
		free(tmp);
	}
	ft_strdel(&pwd);
	return (curpath);
}

int			bi_cd(char **com, char **env)
{
	int		op;
	char	*curpath;

	if ((op = check_options(com[1])))
		++com;
	if (op == -1)
		op = 0;
	if (!com[1] && !is_env_local(env, "HOME"))
		return ((ft_dprintf(2, "cd: HOME not set\n") && 0) - 1);
	if (ft_strequ(com[1], "-") && !is_env_local(env, "OLDPWD"))
		return ((ft_dprintf(2, "cd: OLDPWD not set\n") && 0) - 1);
	curpath = get_curpath(com, env);
	if (!op && (!bi_cd_to_canonical(&curpath) || !curpath))
		return (-1);
	op = do_chdir(curpath, op);
	if (!op && com[1] && ft_strequ(com[1], "-"))
		ft_putendl(get_env("PWD"));
	return (op);
}
