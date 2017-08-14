# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/07 23:21:20 by nmougino          #+#    #+#              #
#    Updated: 2017/08/14 18:50:00 by nmougino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Compilator - clang est plus sur que gcc
CC =		clang
CFLAGS =	-Wall -Wextra -Werror -Weverything -Wno-padded #-fsanitize=address

#	Binary
NAME =		21sh

#	Default rule
DEFRULE =	all

#	Dossiers utiles
SRCDIR =	srcs
INCDIR =	includes
OBJDIR =	objs
DETDIR =	cmdl_treatment env_dep exec get_cmdl history parser tc_misc

#	Liste des sources
# cmdl_treatment/sh_lex_act.c
SRC =		cmdl_treatment/cmdl_treatment.c \
			cmdl_treatment/lex_define_token.c \
			cmdl_treatment/lex_misc.c \
			cmdl_treatment/sh_inhib_exp.c \
			cmdl_treatment/sh_lexer.c \
			cmdl_treatment/syntax_check.c \
			env_dep/env_del.c \
			env_dep/env_display.c \
			env_dep/env_init.c \
			env_dep/get_env.c \
			exec/create_simple.c \
			exec/exec_simple.c \
			exec/get_cmd_path.c \
			exec/handle_redir.c \
			exec/parse_redir.c \
			get_cmdl/get_cmdl.c \
			get_cmdl/get_cmdl_notc.c \
			get_cmdl/handle_actions.c \
			get_cmdl/handle_alt_arrows.c \
			get_cmdl/handle_alt_key.c \
			get_cmdl/handle_arrows.c \
			get_cmdl/handle_back_slash.c \
			get_cmdl/handle_del.c \
			get_cmdl/handle_home_end.c \
			get_cmdl/handle_quotes.c \
			get_cmdl/print_cmdl.c \
			history/destroy_history.c \
			history/history_add.c \
			history/history_dep.c \
			history/history_misc.c \
			main.c \
			metainit.c \
			parser/add_to_ast.c \
			parser/ast_parser.c \
			tc_misc/err_dep.c \
			tc_misc/sh_go_doup.c \
			tc_misc/tc_putc.c \
			tc_misc/term_check.c \
			tc_misc/terminit.c
LIB =		ft
OBJ =		$(SRC:.c=.o)

#	Prefixes
LLIBP =		$(addprefix -l, $(LIB))
LIBP =		$(addprefix lib, $(LIB))
OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#	Couleurs
DEF =		\033[0m
GRA =		\033[1m
SOU =		\033[4m
BLI =		\033[5m
BLA =		\033[30m
RED =		\033[31m
GRE =		\033[32m
YEL =		\033[33m
BLU =		\033[34m
PUR =		\033[35m
CYA =		\033[36m
WHI =		\033[37m

define \n


endef

# #
#	RULES
#

.PHONY = default glu all re libcomp $(OBJDIR) $(NAME) clean fclean

ifneq ($(wildcard /Users/nmougino/.brew/bin/lolcat), "")
	LOLCAT = | lolcat -F 0.25
endif


UNICORN = "\n \t     \\ \n \t      \\ \n \t       \\\\ \n \t        \\\\ \n \t         >\\/7 \n \t     _.-(6\'  \\          Unicorns get the shit done\n \t    (=___._/\` \\ \n \t         )  \ | \n \t        /   / | \n \t       /    > / \n \t      j    < _\ \n \t  _.-\' :      \`\`. \n \t  \\ r=._\\        \`. \n \t <\`\\\\_  \\         .\`-. \n \t  \\ r-7  \`-. ._  \' .  \`\\ \n \t   \\\`,      \`-.\`7  7)   ) \n \t    \\/         \\|  \\\'  / \`-._ \n \t               ||    .\'                   Be more unicorn.\n \t                \\  ( \n \t                 >\\  > \n \t             ,.-\' >.\' \n \t            <.\'_.\'\' \n \t              <\' \n"

#	Main rules
default:
	@echo "$(GRA)  DEFAULT RULE EXECUTION  :::  rule $(DEFRULE)$(DEF)"
	@$(addprefix make ,$(DEFRULE))
	@echo "$(GRE)$(GRA)Programme termine :)$(DEF)"
	@echo $(UNICORN) $(LOLCAT)

glu: re
	make clean

all: libcomp $(OBJDIR) $(NAME)

re: fclean all
	@echo $(UNICORN) $(LOLCAT)

reloc: fcleanloc all

#	Compilation rules
libcomp:
	make all -C lib$(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(CC) $(CFLAGS)	$(ADDFLAGS) -c -o $@ $^ -I $(INCDIR)" $(LOLCAT)
	@$(CC) $(CFLAGS)	$(ADDFLAGS) -c -o $@ $^ -I $(INCDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(addprefix "$(OBJDIR)/", $(DETDIR))
	@echo "$(GRA)$(CYA)@ ++ Objects compilation$(DEF)"

$(NAME): $(OBJP)
	@echo "$(GRA)$(CYA)@ ++ $@ compilation$(DEF)"
	@$(CC) $(CFLAGS) $(ADDFLAGS)	-o $@ $^ -I $(INCDIR) -ltermcap -L lib$(LIB) -l$(LIB)

#	MrProper's legacy
cleanloc:
	@echo "$(RED)@ Objects deletion$(DEF)"
	@rm -rf $(OBJDIR)


clean: cleanloc
	@echo "$(RED)@ Library deletion$(DEF)"
	@make fclean -C libft/

fcleanloc: cleanloc
	@echo "$(RED)@ Binary deletion$(DEF)"
	@rm -f $(NAME)

fclean: clean
	@echo "$(RED)@ Binary deletion$(DEF)"
	@rm -f $(NAME)
