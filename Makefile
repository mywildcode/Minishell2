# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/04 12:08:08 by ql-eilde          #+#    #+#              #
#    Updated: 2015/01/30 16:14:31 by ql-eilde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell2

SRC = minishell2.c gnl/get_next_line.c builtins.c other_functions1.c \
	  other_functions2.c other_functions3.c

OBJ = minishell2.o get_next_line.o builtins.o other_functions1.o \
	  other_functions2.o other_functions3.o

FLAGS = -Wall -Wextra -Werror

LFTFLAGS = -L libft/ -lft

all: $(NAME)

$(NAME):
	@make -C libft/ fclean
	@make -C libft/
	@gcc $(FLAGS) -I libft/ -c gnl/get_next_line.c
	@gcc $(FLAGS) -I libft/ -c minishell2.c
	@gcc $(FLAGS) -I libft/ -c builtins.c
	@gcc $(FLAGS) -I libft/ -c other_functions1.c
	@gcc $(FLAGS) -I libft/ -c other_functions2.c
	@gcc $(FLAGS) -I libft/ -c other_functions3.c
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
