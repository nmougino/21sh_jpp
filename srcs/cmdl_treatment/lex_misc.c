/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 21:15:07 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/06 21:17:21 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*which_operator(char *cmdl)
{
	if (ft_strnequ(DLESS, cmdl, ft_strlen(DLESS)))
		return (DLESS);
	else if (ft_strnequ(DGREAT, cmdl, ft_strlen(DGREAT)))
		return (DGREAT);
	else if (ft_strnequ(LESSAND, cmdl, ft_strlen(LESSAND)))
		return (LESSAND);
	else if (ft_strnequ(GREATAND, cmdl, ft_strlen(GREATAND)))
		return (GREATAND);
	else if (ft_strnequ(AND_IF, cmdl, ft_strlen(AND_IF)))
		return (AND_IF);
	else if (ft_strnequ(OR_IF, cmdl, ft_strlen(OR_IF)))
		return (OR_IF);
	else if (ft_strnequ(PIPE, cmdl, ft_strlen(PIPE)))
		return (PIPE);
	else if (ft_strnequ(AMPERSAND, cmdl, ft_strlen(AMPERSAND)))
		return (AMPERSAND);
	else if (ft_strnequ(SEMI, cmdl, ft_strlen(SEMI)))
		return (SEMI);
	else if (ft_strnequ(LESS, cmdl, ft_strlen(LESS)))
		return (LESS);
	else if (ft_strnequ(GREAT, cmdl, ft_strlen(GREAT)))
		return (GREAT);
	return (NO_OP);
}

enum e_token_type	is_operator(char *cmdl)
{
	if (ft_strnequ(DLESS, cmdl, ft_strlen(DLESS)) ||
		ft_strnequ(DGREAT, cmdl, ft_strlen(DGREAT)) ||
		ft_strnequ(LESSAND, cmdl, ft_strlen(LESSAND)) ||
		ft_strnequ(GREATAND, cmdl, ft_strlen(GREATAND)) ||
		ft_strnequ(LESS, cmdl, ft_strlen(LESS)) ||
		ft_strnequ(GREAT, cmdl, ft_strlen(GREAT)))
		return (OP_REDIRECT);
	else if (ft_strnequ(AND_IF, cmdl, ft_strlen(AND_IF)) ||
		ft_strnequ(OR_IF, cmdl, ft_strlen(OR_IF)) ||
		ft_strnequ(PIPE, cmdl, ft_strlen(PIPE)) ||
		ft_strnequ(AMPERSAND, cmdl, ft_strlen(AMPERSAND)) ||
		ft_strnequ(SEMI, cmdl, ft_strlen(SEMI)))
		return (OP_CONTROL);
	return (WORD);
}
