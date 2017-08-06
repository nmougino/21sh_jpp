/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 18:37:28 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/06 21:02:17 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			syntax_check(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		if (((t_token*)(cur->content))->type > NEWLINE && cur == lst)
			return (ft_printf("sh : syntax error near '%s'\n",
			((t_token*)(cur->content))->content) && 0);
		else if (((t_token*)(cur->content))->type > IO_NUMBER && !(cur->next))
			return (ft_printf("sh : syntax error near '%s'\n",
			((t_token*)(cur->content))->content) && 0);
		else if (((t_token*)(cur->content))->type > IO_NUMBER &&
			((t_token*)(cur->next->content))->type > IO_NUMBER)
			return (ft_printf("sh : syntax error near '%s'\n",
			((t_token*)(cur->content))->content) && 0);
			cur = cur->next;
	}
	return (1);
}
