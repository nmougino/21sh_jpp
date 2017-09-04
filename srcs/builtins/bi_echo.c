/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 19:36:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/04 18:43:37 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	bi_echo_setop(char *c)
{
	if (*c != '-' || *(++c) != 'n')
		return (0);
	while (*c)
	{
		if (*c != 'n')
			return (0);
		++c;
	}
	return (1);
}

int			bi_echo(char **com, char **env)
{
	int	i;

	(void)env;
	i = com[1] ? bi_echo_setop(com[1]) : 0;
	com += i + 1;
	while (*com)
	{
		ft_putstr(*com);
		if (*(com + 1))
			ft_putchar(' ');
		++com;
	}
	if (!i)
		ft_putchar('\n');
	return (0);
}
