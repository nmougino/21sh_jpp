/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 23:04:01 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/25 12:13:20 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		sh_explim(char c)
{
	return (!(ft_isalnum(c) || c == '_'));
}

void			handle_expansion(char **str, size_t *i)
{
	char	*tmp;
	size_t	len;
	char	*name;

	len = ft_wordlen(*str + *i + 1, sh_explim);
	name = ft_strndup(*str + *i + 1, len);
	if ((tmp = get_env(name)))
		replace_expansion(str, tmp, i, name);
	else
	{
		++len;
		while (!tmp && len--)
			ft_move_left(*str + *i);
	}
	free(name);
	(*i)--;
}
