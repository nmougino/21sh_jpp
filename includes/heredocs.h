/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:09:07 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/28 21:37:37 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOCS_H
# define HEREDOCS_H

/*
** handle_heredoc.c
*/

void	handle_heredoc(char **dest);

/*
** hd_parser.c
*/

void	hd_parser(t_btree **r);

/*
** write_hd.c
*/

void	write_hd(t_com *com, int save[]);

#endif
