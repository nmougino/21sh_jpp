/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quotes_aliases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 06:18:46 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 00:39:44 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** QACD
** Quotes and Aliases Conversion Departement
*/

static void		quote_act(char c, int *q)
{
	if (!*q && c == '\'')
		*q = 1;
	else if (!*q && c == '"')
		*q = 2;
	else if (c == '\'' && *q == 1)
		*q = 0;
	else if (c == '"' && *q == 2)
		*q = 0;
}

void	sh_quotes_aliases(t_list *lst)
{
	char	*str;
	int		q;
	int		i;

	str = lst->content;
	q = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_strchr("\"'", str[i]) && !(i && str[i - 1] != '\\'))
		{
			quote_act(str[i], &q);
			ft_move_left(str + i--);
		}
		// else if (str[i] == '$' && (!q || q == 2))
	}
}
