/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:06:02 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 15:07:24 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/stat.h>

typedef struct	s_com
{
	char		*cmd_path;
	char		**cmd_args;
	int			fd[3];
	int			to_close[3];
}				t_com;

int				get_cmd_path(t_list *lst, t_com *com);
void			handle_redir(t_list *cmdl, t_com *com);
void			exec_simple(t_list *lst);

#endif
