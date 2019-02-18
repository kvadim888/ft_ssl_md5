# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 00:10:36 by vkryvono          #+#    #+#              #
#    Updated: 2018/10/23 00:07:05 by vkryvono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC			=	gcc
FLAGS 		=	-Wall -Wextra -Werror

INC_PATH	=	./inc
SRC_PATH	=	./src
OBJ_PATH	=	./obj

SRC			=	main.c\
				ft_md5base.c\
				ft_md5loop.c\
				ft_sha256base.c\
				ft_display.c\
				ft_utils.c

OBJ			=	$(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))

INC			=	-I./libft/includes\
				-I./inc

LIBFT 		=	-L./libft -lft

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) $(INC) -o $@ -c $< #$(FLAGS)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
