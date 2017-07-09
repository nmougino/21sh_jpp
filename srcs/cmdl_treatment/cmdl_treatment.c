/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 16:19:44 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/09 22:28:56 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ct_destroy(void *p, size_t s)
{
	free(p);
	(void)s;
}

char		**cmdl_treatment(t_cmdl *cmdl)
{
	char	**ans;
	t_list	*lst;

	lst = sh_lexer(cmdl->cmdl);
	ans = ft_lststrtotab(lst);
	ft_lstdel(&lst, ct_destroy);
	return (ans);
}
