/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 18:37:28 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/06 18:57:00 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	lex_put_error(t_list *cur)
{
	ft_printf("sh : syntax error near '%s'\n",
		((t_token*)(cur->content))->content);
	return (0);
}

int			syntax_check(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		if (((t_token*)(cur->content))->type > NEWLINE && cur == lst)
			return (lex_put_error(cur));
		else if (((t_token*)(cur->content))->type > IO_NUMBER && !(cur->next))
			return (lex_put_error(cur));
		else if (((t_token*)(cur->content))->type > IO_NUMBER &&
			((t_token*)(cur->next->content))->type > IO_NUMBER)
			return (lex_put_error(cur));
		cur = cur->next;
	}
	return (1);
}
