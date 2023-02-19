# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 20:47:27 by amitcul           #+#    #+#              #
#    Updated: 2023/02/19 14:30:52 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lexer.a

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -f
AR		=	ar rc
RN		=	ranlib

O_DIR = ./obj
I_DIR = ./../../includes

# SOURCES := $(wildcard *.c)
SOURCES := lexer.c doubly_linked_list_utils.c
OBJECTS := $(SOURCES:.c=.o)

OBJECTS_DIR := $(addprefix $(O_DIR)/,$(OBJECTS))

all: start $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c -I$(I_DIR) $< -o $(O_DIR)/$@

start:
	@if test -d $(O_DIR); then echo lexer $(O_DIR) exist; else mkdir $(O_DIR); fi

$(NAME): $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS_DIR)
	@$(RN) $(NAME)

debug: all
	$(CC) $(CFLAGS) main.c $(NAME) libft.a

d: debug

clean:
	@rm -rf $(O_DIR)

fclean: clean
	@rm -rf a.out
	@rm -rf $(NAME)
	@rm -rf $(O_DIR)

re: fclean all
