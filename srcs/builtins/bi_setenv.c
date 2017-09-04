/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 18:58:04 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/04 19:27:17 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	bi_setenv_iserror(char **com)
{
	int		i;
	char	*tmp;

	i = 0;
	i = (!com || !com[1] || !com[1][0]) ? 1 : 0;
	++com;
	while (!i && *com)
	{
		tmp = ft_strchr(*com, '=');
		if (!tmp || tmp == *com)
			i = 1;
		++com;
	}
	if (i)
	{
		ft_dprintf(2, "setenv: usage: setenv KEY=VALUE [KEY=VALUE ...]\n");
		return (1);
	}
	return (0);
}

int			bi_setenv(char **com, char **env)
{
	t_shenv	new;
	size_t	i;

	(void)env;
	if (bi_setenv_iserror(com))
		return (-1);
	++com;
	while (*com)
	{
		i = (size_t)ft_strcloc('=', *com);
		new.name = ft_strnew(i);
		ft_strncpy(new.name, *com, i);
		new.cont = ft_strdup((*com) + i + 1);
		env_set(new.name, new.cont);
		free(new.name);
		free(new.cont);
		++com;
	}
	return (0);
}
