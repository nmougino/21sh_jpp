/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:54:18 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/13 17:42:44 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	do_it_han_red(char *tok, int io, t_com *com, char *next)
{
	int	tmp;

	if (!ft_strcmp(tok, LESS)) // "<"
	{
		if ((tmp = ft_open(next, O_CREAT | O_RDONLY, "sh")) != -1)
			com->fd[io == -1 ? 0 : io] = tmp;
	}
	else if (!ft_strcmp(tok, GREAT)) // ">"
	{
		if ((tmp = ft_open(next, O_CREAT | O_WRONLY | O_TRUNC, "sh")) != -1)
			com->fd[io == -1 ? 1 : io] = tmp;
	}
	else if (!ft_strcmp(tok, DGREAT)) // ">>"
	{
		if ((tmp = ft_open(next, O_CREAT | O_WRONLY, "sh")) != -1)
			com->fd[io == -1 ? 1 : io] = tmp;
	}
	else if (!ft_strcmp(tok, LESSAND)) // "<&"
		com->fd[io == -1 ? 1 : -1] = ft_atoi(next);
	else if (!ft_strcmp(tok, GREATAND)) // ">&"
		com->fd[io == -1 ? 0 : -1] = ft_atoi(next);
}

static void	parse_redir(t_list *cmdl, t_com *com)
{
	int	tmp;

	tmp = -1;
	while (cmdl)
	{
		if (((t_token*)(cmdl->content))->type == IO_NUMBER)
			tmp = ft_atoi(((t_token*)(cmdl->content))->content);
		else if ((((t_token*)(cmdl->content))->type == OP_REDIRECT) &&
			!ft_strcmp(((t_token*)(cmdl->next->content))->content, "-"))
			com->to_close[tmp == -1 ? 1 : tmp] = 1;
		else if (((t_token*)(cmdl->content))->type == OP_REDIRECT)
		{
			do_it_han_red(((t_token*)(cmdl->content))->content, tmp, com,
			(((t_token*)(cmdl->next->content))->content));
			tmp = -1;
		}
		cmdl = cmdl->next;
	}
}

void		handle_redir(t_list *cmdl, t_com *com)
{
	parse_redir(cmdl, com);
	dup2(com->fd[0], 0);
	dup2(com->fd[1], 1);
	dup2(com->fd[2], 2);
	if (com->to_close[0])
		close(0);
	if (com->to_close[1])
		close(1);
	if (com->to_close[2])
		close(2);
}
