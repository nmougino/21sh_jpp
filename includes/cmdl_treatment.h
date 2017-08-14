/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_treatment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:28:53 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 15:35:27 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDL_TREATMENT_H
# define CMDL_TREATMENT_H

enum					e_token_type {
	WORD,
	NEWLINE,
	IO_NUMBER,
	OP_REDIRECT,
	OP_CONTROL
};

# define NO_OP NULL

// REDIRECTION
# define LESS "<"
# define GREAT ">"
# define DLESS "<<"
# define DGREAT ">>"
# define LESSAND "<&"
# define GREATAND ">&"

// CONTROL
# define AMPERSAND "&"
# define AND_IF "&&"
# define OR_IF "||"
# define PIPE "|"
# define SEMI ";"
// # define DSEMI ";;"
// # define LESSGREAT "<>"
// # define DLESSDASH "<<-"
// # define CLOBBER ">|"

typedef struct			s_token
{
	enum e_token_type	type;
	char				*content;
}						t_token;

/*
** cmdl_treatment.c
*/

t_list	*cmdl_treatment(t_cmdl *cmdl);

/*
** lex_define_token.c
*/

void					lex_define_prev_token(char **cmdl, int *j,
							t_list **lst);
void					lex_define_ionum_token(char **cmdl, t_list **lst);
void					lex_define_op_token(char **cmdl, t_list **lst);

/*
** lex_misc.c
*/

char					*which_operator(char *cmdl);
enum e_token_type		is_operator(char *cmdl);

/*
** sh_inhib_exp.c
*/

void					sh_inhib_exp(t_list *lst);

/*
** sh_lexer.c
*/

t_list					*sh_lexer(char *cmdl);

/*
** syntax_check.c
*/

int						syntax_check(t_list *lst);

#endif
