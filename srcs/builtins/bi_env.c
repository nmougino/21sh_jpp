/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 17:25:49 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/23 20:08:02 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	bi_env_check_options(char *str)
{
	if (!str || !(*str) || *str != '-')
		return (0);
	++str;
	while (*str)
	{
		if (*str != 'i')
		{
			ft_dprintf(2, "env: illegal option -- %c\n", *str);
			return (-1);
		}
		++str;
	}
	return (1);
}

static void	env_set_loc(char *tar, char *new_cont)
{
	t_list	*tmp;
	t_shenv	new;

	tmp = g_meta.shenv;
	while (tmp && ft_strcmp(((t_shenv*)(tmp->content))->name, tar))
		tmp = tmp->next;
	if (!tmp)
	{
		new.name = ft_strdup(tar);
		new.cont = ft_strdup(new_cont);
		ft_lstadd_end(&(g_meta.shenv), ft_lstnew(&new, sizeof(t_shenv)));
	}
	else
	{
		ft_strdel(&(((t_shenv*)(tmp->content))->cont));
		((t_shenv*)(tmp->content))->cont = ft_strdup(new_cont);
	}
}

static char	**bi_env_cpy_env(char **com, char **env, char ***new_env)
{
	size_t	i;
	size_t	l;
	t_list	*tmp_env;
	t_list	*save;
	char	*new[2];

	save = g_meta.shenv;
	env_init(&tmp_env, env);
	g_meta.shenv = tmp_env;
	i = 0;
	while (com[i] && ft_strchr(com[i], '=') && ft_strchr(com[i], '=') != com[i])
	{
		l = (size_t)(ft_strchr(com[i], '=') - com[i]);
		new[0] = ft_strndup(com[i], l);
		new[1] = ft_strdup(com[i] + l + 1);
		env_set_loc(new[0], new[1]);
		free(new[0]);
		free(new[1]);
		++i;
	}
	*new_env = env_conv();
	ft_lstdel(&(g_meta.shenv), env_del);
	g_meta.shenv = save;
	return (com + i);
}

static int	bi_env_subsh(char **com, char **env)
{
	t_cmdl	cmdl;
	int		i;
	t_btree	*ast_save;

	ast_save = g_meta.ast;
	g_meta.ast = NULL;
	env_init(&(g_meta.shenv), env);
	i = 0;
	cmdl.cmdl = ft_arrglu(com, " ", 1);
	cmdl.pos = 0;
	i = exec_mother(&cmdl);
	g_meta.ast = ast_save;
	ft_strdel(&(cmdl.cmdl));
	ft_lstdel(&(g_meta.shenv), env_del);
	g_meta.shenv = g_meta.shenv_save;
	return (i);
}

int			bi_env(char **com, char **env)
{
	int		i;
	char	**new_env;

	++com;
	new_env = NULL;
	if ((i = bi_env_check_options(com[0])) == -1)
		return (-1);
	else if (i)
	{
		env = NULL;
		++com;
	}
	i = 0;
	com = bi_env_cpy_env(com, env, &new_env);
	new_env = new_env ? new_env : ft_arrstrncpy(com, 0);
	if (!(*com))
		ft_arriter_str(new_env, env_display_local);
	else
		i = (bi_env_subsh(com, new_env));
	ft_arrdel((void***)&new_env);
	return (i);
}
