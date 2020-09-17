# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: memilio <memilio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/17 17:45:53 by memilio           #+#    #+#              #
#    Updated: 2020/09/17 18:05:53 by memilio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRC		=	./srcs/main.c \
			./utils/ft_putchar_fd.c \
			./utils/ft_putstr_fd.c \
			./utils/ft_putendl_fd.c \
			./utils/ft_strchr.c \
			./utils/ft_strcmp.c \
			./utils/ft_strdup_gnl.c \
			./utils/ft_strjoin.c \
			./utils/ft_strlcat.c \
			./utils/ft_strlcpy.c \
			./utils/ft_strlen.c \
			./utils/get_next_line.c
INC		=	./includes/
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re