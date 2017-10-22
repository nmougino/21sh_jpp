/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_close_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 18:25:54 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 20:44:52 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	prepare_exec(t_pre_exec *pre, t_btree *tar)
{
	pre->env = env_conv();
	create_simple(&(pre->com), (t_list *)(tar->data));
	handle_redir(NULL, pre->save);
	if (pre->com.heredoc)
		pipe(pre->com.hdfd);
}

void	close_exec(t_pre_exec *pre)
{
	if (!pre->com.heredoc)
		restore_redir(pre->save);
	com_del(&(pre->com));
	ft_arrdel((void***)&(pre->env));
}
