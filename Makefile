# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/06/03 22:15:50 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

CC		=	cc
CFLAGS	=	-fdiagnostics-color=always -g -Wall -Wextra -Werror
RM		=	rm -rf

LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a

INCLUDES = ./includes/
INCLUDES_LIB = ./libft/includes/

HEADER += $(INCLUDES)minishell.h
HEADER += $(INCLUDES)lexer.h
HEADER += $(INCLUDES)utils.h
HEADER += $(INCLUDES)executor.h
HEADER += $(INCLUDES)parser.h

HEADER += $(INCLUDES)expander.h

LIB_TERMCAP = -lreadline -L./libft -lft

SRCS += main.c signal_handlers.c utils.c
TEST_SRC = test.c

# Lexer source files
SRCS += lexer.c quotes.c tokens.c lexer_utils.c

# Parser source files
SRCS += parser.c parser_error.c command.c parser_utils.c redirections.c

# Builtins source files
SRCS += unset.c env.c echo.c export.c pwd.c exit.c cd.c sig_config.c

# Executor files
SRCS += executor.c heredoc.c handle.c

# Error files
SRCS += error.c error_handling.c

# Expander files
SRCS += expander.c

OBJ_DIR = ./obj/

vpath %.c src/
vpath %.c src/lexer/
vpath %.c src/parser/
vpath %.c src/executor/
vpath %.c src/expander/
vpath %.c src/errors/

vpath %.c src/utils/
vpath %.c src/builtin/unset
vpath %.c src/builtin/env
vpath %.c src/builtin/echo
vpath %.c src/builtin/export
vpath %.c src/builtin/pwd
vpath %.c src/builtin/exit
vpath %.c src/builtin/cd
vpath %.c src/builtin/

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(LIB)
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -fPIE -I $(INCLUDES) -I $(INCLUDES_LIB)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -fPIE $(LIB_TERMCAP)

$(OBJ_DIR):
	mkdir $@

$(LIB):
	$(MAKE) -C $(LIBDIR)

test: $(LIB) $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -D DEBUG -I$(INCLUDES) -I$(INCLUDES_LIB) $(LIB_TERMCAP) -o minishell_$@

fclean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)
	$(RM) -R $(OBJ_DIR)
	$(RM) minishell_test

clean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)

re : fclean
	$(MAKE)
