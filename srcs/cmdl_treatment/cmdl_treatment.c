/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 16:19:44 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/01 21:21:22 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	put_token(t_list *e)
{
	t_token	*tok;

	tok = (t_token*)e->content;
	ft_printf("type = %d, cont = |%s|\n", tok->type, tok->content);
}

t_list		*cmdl_treatment(t_cmdl *cmdl)
{
	t_list	*lst;

	lst = sh_lexer(cmdl->cmdl);
	ft_lstiter(lst, sh_inhib_exp);
	ft_lstiter(lst, put_token);
	return (lst);
}
