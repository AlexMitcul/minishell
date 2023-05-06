# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/05/06 16:11:31 by amitcul          ###   ########.fr        #
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
HEADER += $(INCLUDES)lexer.h
HEADER += $(INCLUDES)utils.h
HEADER += $(INCLUDES)executor.h

LIB_TERMCAP = -lreadline -L./libft -lft

SRCS += m.c

# Lexer source files
# SRCS += lexer.c utils.c states_handler.c types_handler.c expand.c
SRCS += lexer.c quotes.c tokens.c lexer_utils.c

# Parser source files
# SRCS += parser.c pipe.c redirect.c command.c compare.c tree.c

# Utils source files
# SRCS += doubly_linked_list_utils.c env_list.c count_symbol_in_string.c \
# 		env_list_utils.c array_utils.c

# Builtins source files
# SRCS += unset.c env.c echo.c export.c pwd.c exit.c cd.c sig_config.c

# Executor files
# SRCS += executor.c executor_command.c executor_command_utils.c builtins.c \
# 		traverse_tree.c

OBJ_DIR = ./obj/

vpath %.c src/

vpath %.c src/lexer/
# vpath %.c src/lexer/lexer_utils/

# vpath %.c src/parser/

# vpath %.c src/utils/
# vpath %.c src/builtin/unset
# vpath %.c src/builtin/env
# vpath %.c src/builtin/echo
# vpath %.c src/builtin/export
# vpath %.c src/builtin/pwd
# vpath %.c src/builtin/exit
# vpath %.c src/builtin/cd
# vpath %.c src/builtin/

vpath %.c src/executor/

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(LIB)
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -I $(INCLUDES_LIB) -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) $(LIB_TERMCAP) -o $@

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
