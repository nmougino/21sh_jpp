/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:22:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/26 21:37:27 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	bi_cd_err(char *tar)
{
	struct stat	buf;

	if (lstat(tar, &buf))
		ft_dprintf(2, "cd: no such file or directory: %s\n", tar);
	else if (access(tar, F_OK))
		ft_dprintf(2, "cd: file is not accessible: %s\n", tar);
	else if (access(tar, X_OK))
		ft_dprintf(2, "cd: permission denied: %s\n", tar);
	else
		ft_dprintf(2, "cd: unknow error: %s\n", tar);
}

static void	bi_cd_addpwd(t_env *env)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	env_set(env, "OLDPWD", env_get(env, "PWD"));
	env_set(env, "PWD", tmp);
	free(tmp);
}

static void	bi_chdir(t_env *env, char *com)
{
	if (chdir(com))
		bi_cd_err(com);
	else
	{
		if (is_env(env, "PWD"))
		{
			if (!is_env(env, "OLDPWD"))
				env_set(env, "PWD", com);
			else
				bi_cd_addpwd(env);
		}
	}
}

void		bi_cd(char **args, char **env)
{
	if (!com[1])
	{
		if (is_env(env, "HOME"))
			bi_chdir(env, env_get(env, "HOME"));
		else
			ft_dprintf(2, "cd: HOME not set\n");
	}
	else
	{
		if (ft_strcmp("-", com[1]))
			bi_chdir(env, com[1]);
		else if (is_env(env, "OLDPWD"))
			bi_chdir(env, env_get(env, "OLDPWD"));
		else
			ft_dprintf(2, "cd: OLDPWD not set\n");
	}
}
