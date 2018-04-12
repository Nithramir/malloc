# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bandre <bandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/07 16:17:12 by bandre            #+#    #+#              #
#    Updated: 2018/04/12 19:01:27 by bandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc

SRC_PATH = malloc_src

OBJ_PATH = malloc_obj

SRC = malloc.o\
	allocated.o\
	get_memory_place.o\
	ft_search_ptr.o\
	ft_search_size.o\
	show_mem.o\

CC = gcc -g

LIB =  libft/libftprintf.a

FLAG = #-Wall -Wextra -Werror -O

SRC_O = $(addprefix $(OBJ_PATH)/,$(SRC))
SRC_C = $(addprefix $(SRC_PATH)/,$(SRC))

all: EXEC $(NAME)

$(NAME): $(SRC_O)
	$(CC) -shared -o $(NAME) $(SRC_O) $(LIB) $(FLAG)

EXEC: 
	make -C libft

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) -c $< -o $@ $(FLAG)

clean:
	rm -f $(addprefix $(OBJ_PATH)/,$(SRC))
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

flag: $(SRC)
	$(CC) $(NAME) $(LIB) -o $(NAME)

do: all
	./malloc

.PHONY: $(NAME) all %.o clean fclean re flag EXEC
