# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/07 23:21:20 by nmougino          #+#    #+#              #
#    Updated: 2017/07/05 00:14:58 by nmougino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Compilator - clang est plus sur que gcc
CC =		clang
CFLAGS =	-Wall -Wextra -Werror -Weverything -Wno-padded
#-Wno-padded

#	Binary
NAME =		21sh

#	Default rule
DEFRULE =	all

#	Dossiers utiles
SRCDIR =	srcs
INCDIR =	includes
OBJDIR =	objs

#	Liste des sources
SRC =		err_dep.c \
			destroy_history.c \
			get_cmdl.c \
			handle_alt_arrows.c \
			handle_alt_key.c \
			handle_arrows.c \
			handle_del.c \
			handle_home_end.c \
			history_dep.c \
			main.c \
			metainit.c \
			sh_go_doup.c \
			print_cmdl.c \
			tc_putc.c \
			terminit.c
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

#	Main rules
default:
	@echo "$(GRA)  DEFAULT RULE EXECUTION  :::  rule $(DEFRULE)$(DEF)"
	@$(addprefix make ,$(DEFRULE))
	@echo "$(GRE)$(GRA)Programme termine :)$(DEF)"

glu: re
	make clean

all: libcomp $(OBJDIR) $(NAME)

re: fclean all

#	Compilation rules
libcomp:
	make all -C lib$(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(CC) $(CFLAGS)	$(ADDFLAGS) -c -o $@ $^ -I $(INCDIR)" | lolcat
	@$(CC) $(CFLAGS)	$(ADDFLAGS) -c -o $@ $^ -I $(INCDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(GRA)$(CYA)@ ++ Objects compilation$(DEF)"

$(NAME): $(OBJP)
	@echo "$(GRA)$(CYA)@ ++ $@ compilation$(DEF)"
	@$(CC) $(CFLAGS) $(ADDFLAGS)	-o $@ $^ -I $(INCDIR) -ltermcap -L lib$(LIB) -l$(LIB)

#	MrProper's legacy
clean:
	@echo "$(RED)@ Objects deletion$(DEF)"
	@rm -rf $(OBJDIR)
	@echo "$(RED)@ Library deletion$(DEF)"
	@make fclean -C libft/

fclean: clean
	@echo "$(RED)@ Binary deletion$(DEF)"
	@rm -f $(NAME)
