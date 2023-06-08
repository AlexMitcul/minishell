# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/06/05 21:23:21 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -rf

LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a

INCLUDES = ./includes/
INCLUDES_LIB = ./libft/includes/

HEADER += $(INCLUDES)minishell.h
HEADER += $(INCLUDES)utils.h
HEADER += $(INCLUDES)lexer.h
HEADER += $(INCLUDES)parser.h
HEADER += $(INCLUDES)expander.h

LIB_TERMCAP = -lreadline

SRCS += main.c

# Error files
SRCS += error.c

# Lexer source files
SRCS += quotes.c tokens.c lexer_utils.c lexer_tester.c

# Parser source files
SRCS += parser.c command.c parser_utils.c redirections.c parser_test.c

# Expander files
SRCS += expander.c expander_utils.c

# Utils source files
SRCS += doubly_linked_list_utils.c env_list.c count_symbol_in_string.c

# Builtins source files
# SRCS += unset.c env.c echo.c export.c pwd.c exit.c cd.c sig_config.c

OBJ_DIR = ./obj/

vpath %.c src/

vpath %.c src/error/

vpath %.c src/lexer/
vpath %.c src/parser/
vpath %.c src/expander/

vpath %.c src/utils/
# vpath %.c src/builtin/unset
# vpath %.c src/builtin/env
# vpath %.c src/builtin/echo
# vpath %.c src/builtin/export
# vpath %.c src/builtin/pwd
# vpath %.c src/builtin/exit
# vpath %.c src/builtin/cd
# vpath %.c src/builtin/

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(LIB)
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -I $(INCLUDES_LIB) -o $@ -fPIE

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) $(LIB_TERMCAP) -L./libft -lft -o $@ -fPIE

$(OBJ_DIR):
	mkdir $@

$(LIB):
	$(MAKE) -C $(LIBDIR)

fclean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)
	$(RM) -R $(OBJ_DIR)

clean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)

re : fclean
	$(MAKE)
