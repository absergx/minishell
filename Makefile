# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: memilio <memilio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/17 17:45:53 by memilio           #+#    #+#              #
#    Updated: 2020/10/06 16:27:53 by memilio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
FUNC	=	main.c \
			ft_parse.c \
			ft_envp_processing.c \
			ft_execute.c \
			commands/ft_cd.c \
			commands/ft_echo.c \
			commands/ft_env.c \
			commands/ft_exit.c \
			commands/ft_export.c \
			commands/ft_pwd.c \
			commands/ft_unset.c \
			ft_handle_signal.c \
			ft_error.c
SRC_DIR	=	./srcs/
SRC		=	$(addprefix $(SRC_DIR), $(FUNC))
INC		=	-I./includes/ -I$(LFT_DIR)
CC		=	gcc
LFT_DIR	=	./libft/
LFT_FLG	=	-L$(LFT_DIR) -lft
FLAGS	=	-Wall -Wextra -Werror -g
OBJ		=	$(SRC:.c=.o)

all: lft $(NAME)
	@echo "\033[32m[+] Make completed\033[0m"

%.o: %.c
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(INC) $(LFT_FLG) -o $(NAME)

lft:
	@$(MAKE) -C $(LFT_DIR) --silent
	@$(MAKE) bonus -C $(LFT_DIR) --silent
	@echo  "\033[32m[+] Libft builded\033[0m"

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re