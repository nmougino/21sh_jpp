/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:23:01 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/28 06:36:47 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	misc_env(void)
{
	int		i;
	char	*s;

	if (is_env("SHLVL"))
	{
		ft_printf("ICI\n");
		i = ft_atoi(get_env("SHLVL")) + 1;
		env_set("SHLVL", s = ft_itoa(i));
		free(s);
	}
	else
		env_add("SHLVL", "1");
	s = getcwd(NULL, 0);
	s = ft_stradd(&s, "/21sh");
	if (is_env("SHELL"))
		env_set("SHELL", s);
	else
		env_add("SHELL", s);
	free(s);
}

void		env_init(t_list **shenv, char **env)
{
	t_shenv	new;
	size_t	i;

	*shenv = NULL;
	if (!env || !*env)
		return ;
	while (*env)
	{
		i = (size_t)ft_strcloc('=', *env);
		new.name = ft_strnew(i);
		ft_strncpy(new.name, *env, i);
		new.cont = ft_strdup((*env) + i + 1);
		ft_lstadd_end(shenv, ft_lstnew(&new, sizeof(t_shenv)));
		++env;
	}
	misc_env();
	ft_lstiter(g_meta.shenv, env_display);
}
