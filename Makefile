# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjanik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/12 10:30:25 by bjanik            #+#    #+#              #
#    Updated: 2017/05/05 14:32:57 by bjanik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBFT  = libft

LIB = libft/libft.a

HEADER = includes

SRC_PATH = srcs
OBJ_PATH = obj

SRC_NAME = errors.c \
	   main.c \
	   ft_cd.c \
	   ft_cd_bis.c \
	   ft_echo.c \
	   ft_env.c \
	   ft_exit.c \
	   ft_setenv.c \
	   ft_unsetenv.c \
	   init_minishell.c \
	   linked_list.c \
	   tools.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all : $(NAME)

$(NAME) : $(OBJ)
	make -C $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

$(OBJ) : $(OBJ_PATH)

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(FLAGS) -I$(HEADER) -I$(LIBFT) -c $< -o $@

clean :
	rm -rf $(OBJ_PATH)
	make clean -C $(LIBFT)

fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re : fclean all
