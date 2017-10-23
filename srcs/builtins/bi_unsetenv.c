/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 19:34:31 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/23 16:40:29 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	bi_unsetenv_iserror(char **com)
{
	int		i;

	i = (!com || !com[1] || !com[1][0]);
	++com;
	while (*com)
	{
		if (!is_env(*com))
		{
			ft_dprintf(2, "unsetenv: %s: not in environment\n", *com);
			return (1);
		}
		++com;
	}
	if (i)
	{
		ft_dprintf(2, "unsetenv: usage: unsetenv KEY [KEY ...]\n");
		return (1);
	}
	return (0);
}

int			bi_unsetenv(char **com, char **env)
{
	(void)env;
	if (bi_unsetenv_iserror(com))
		return (-1);
	while (*com)
	{
		env_unset(*com);
		++com;
	}
	return (0);
}
