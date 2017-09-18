/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:03:39 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/18 11:48:56 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	hd_parser(t_btree **r)
{
	t_list	*lst;

	lst = (t_list*)((*r)->data);
	while (lst)
	{
		if (!ft_strcmp(((t_token*)(lst->content))->content, "<<"))
			handle_heredoc(&(((t_token*)(lst->next->content))->content));
		lst = lst->next;
	}
}
