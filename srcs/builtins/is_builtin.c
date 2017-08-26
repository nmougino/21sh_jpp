/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 18:36:06 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/26 20:42:30 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_builtin(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	i = ft_strequ("echo", str) ? 1 : i;
	i = ft_strequ("cd", str) ? 2 : i;
	i = ft_strequ("setenv", str) ? 3 : i;
	i = ft_strequ("unsetenv", str) ? 4 : i;
	i = ft_strequ("env", str) ? 5 : i;
	i = ft_strequ("exit", str) ? 6 : i;
	return (i);
}
