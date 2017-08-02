/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 16:19:44 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/02 16:47:41 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list		*cmdl_treatment(t_cmdl *cmdl)
{
	t_list	*lst;

	lst = sh_lexer(cmdl->cmdl);
	ft_lstiter(lst, sh_inhib_exp);
	return (lst);
}
