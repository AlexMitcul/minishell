# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 20:47:27 by amitcul           #+#    #+#              #
#    Updated: 2023/02/18 21:56:49 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lexer.a

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
AR		=	ar rc
RN		=	ranlib

O_DIR = ./obj
I_DIR = ./../../includes

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

OBJECTS_DIR := $(addprefix $(O_DIR)/,$(OBJECTS))

all: start $(NAME)

%.o : %.c
	@$(CC) -c -I$(I_DIR) $< -o $(O_DIR)/$@

start:
	@if test -d $(O_DIR); then echo lexer $(O_DIR) exists; else mkdir $(O_DIR); fi

$(NAME): $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS_DIR)
	@$(RN) $(NAME)

clean:
	@rm -rf $(O_DIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(O_DIR)

