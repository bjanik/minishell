# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjanik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/12 10:30:25 by bjanik            #+#    #+#              #
#    Updated: 2017/04/26 17:38:39 by bjanik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBFT  = libft

LIB = libft/libft.a

HEADER = includes

SRCS = srcs/main.c \
	   srcs/ft_cd.c \
	   srcs/ft_echo.c \
	   srcs/ft_env.c \
	   srcs/ft_exit.c \
	   srcs/ft_setenv.c \
	   srcs/ft_unsetenv.c \
	   srcs/init_minishell.c \
	   srcs/linked_list.c \

all : $(NAME)

$(NAME) :
	make -C $(LIBFT)
	$(CC) $(FLAGS) $(SRCS) $(LIB) -I $(HEADER) -I $(LIBFT) -o $(NAME)

clean :
	make clean -C $(LIBFT)

fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re : fclean all

