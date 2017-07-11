/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 17:19:30 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 18:39:39 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	term_check(void)
{
	if (!g_meta.shenv)
		return (0);
	else if(!tgetstr("sf", NULL))
		return (0);
	else if(!tgetstr("ce", NULL))
		return (0);
	else if(!tgetstr("le", NULL))
		return (0);
	else if(!tgetstr("up", NULL))
		return (0);
	return (1);
}
