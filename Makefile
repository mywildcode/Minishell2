# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/04 12:08:08 by ql-eilde          #+#    #+#              #
#    Updated: 2015/02/03 15:47:32 by ql-eilde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell2

SRC = main.c get_next_line.c func1.c func2.c pipe.c init.c \
		controller.c exec.c builtins.c redir.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LFTFLAGS = -L libft/ -lft

all: $(NAME)

$(NAME):
	@make -C libft/ fclean
	@make -C libft/
	@gcc $(FLAGS) -I libft/ -c get_next_line.c
	@gcc $(FLAGS) -I libft/ -c main.c
	@gcc $(FLAGS) -I libft/ -c builtins.c
	@gcc $(FLAGS) -I libft/ -c func1.c
	@gcc $(FLAGS) -I libft/ -c func2.c
	@gcc $(FLAGS) -I libft/ -c pipe.c
	@gcc $(FLAGS) -I libft/ -c init.c
	@gcc $(FLAGS) -I libft/ -c controller.c
	@gcc $(FLAGS) -I libft/ -c exec.c
	@gcc $(FLAGS) -I libft/ -c redir.c
	@gcc -o $(NAME) $(OBJ) $(LFTFLAGS)
	@echo "$(NAME) has been created"

clean:
	@rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "$(NAME) has been deleted"

re: fclean all
