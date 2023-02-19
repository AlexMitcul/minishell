# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/02/19 17:57:53 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

LIBS_DIR = ./libs

LIBFT	=	libft
LIBFT_NAME = libft.a

LEXER	=	src/lexer

OBJ_DIR = ./obj

INCLUDES = includes

SRC_DIR	= src
SOURCES_WITH_DIR := $(shell find $(SRC_DIR) -name "*.c")
DIR = $(dir $(SOURCES_WITH_DIR))
SOURCES := $(notdir $(shell find $(SRC_DIR) -name "*.c"))

OBJECTS := $(SOURCES:.c=.o)
OBJECTS_WITH_DIR = $(addprefix $(OBJ_DIR)/, $(OBJECTS))

all: start lib $(NAME)

$(NAME): $(OBJECTS_WITH_DIR)
	$(CC) $(CFLAGS) -o $(OBJECTS_WITH_DIR) -L ./libs/ -lft main.c
# $(CC) $(CFLAGS) main.c $(OBJECTS_WITH_DIR) -L ./libs/ -lft -o $(NAME) -I $(INCLUDES)

$(OBJ_DIR)/%.o: $(SOURCES_WITH_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

start:
	@if test -d $(OBJ_DIR); then echo $(OBJ_DIR) exist; else mkdir $(OBJ_DIR); fi
	@if test -d $(LIBS_DIR); then echo $(LIBS_DIR) exists; else mkdir $(LIBS_DIR); fi

lib:
	@make -C $(LIBFT)
	@cp $(LIBFT)/$(LIBFT_NAME) $(LIBS_DIR)

clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT)
	$(RM) $(LIBS_DIR)

re: fclean all

