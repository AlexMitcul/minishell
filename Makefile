# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/02/18 21:57:55 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
AR		=	ar rc
RN		=	ranlib

LIBS_DIR = ./libs

LIBFT	=	libft
LEXER	=	src/lexer

O_DIR = ./obj

SOURCES := src/main.c
OBJECTS := $(SOURCES:.c=.o)

all: start lib lexer $(NAME)

start:
	@if test -d $(O_DIR); then echo $(O_DIR) exist; else mkdir $(O_DIR); fi
	@if test -d $(LIBS_DIR); then echo $(LIBS_DIR) exists; else mkdir $(LIBS_DIR); fi

lib:
	@make -C $(LIBFT)
	@cp $(LIBFT)/libft.a ./libs/

lexer:
	@make -C $(LEXER)
	@cp $(LEXER)/lexer.a ./libs/

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) libs/*.a

clean:
	$(RM) $(O_DIR)
	make clean -C $(LIBFT)
	make clean -C $(LEXER)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(LEXER)

re: fclean all

