# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/02/16 13:51:26 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

LIBFT = libft

SRC := $(shell find -wholename "./src/*.c" -type f)
SRCFILES := $(basename $(SRC))

OBJ_DIR		= obj/

OBJ := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(SRCFILES))))
OBJFILES := $(patsubst %.c, %.o, $(OBJ))


all: start $(NAME)

start:
	echo $(OBJ)
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a .

$(OBJF):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJFILES)

fclean: clean
	rm -rf $(NAME)
	rm -rf libft.a

re: fclean all

