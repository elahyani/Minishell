# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 18:19:02 by elahyani          #+#    #+#              #
#    Updated: 2020/11/14 14:36:21 by elahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

SRCS =	cmds.c \
		debug.c

SRC_GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

OBJ_GNL = $(SRC_GNL:.c=.o)

LIBFT = ./libft/libft.a

MAIN = main.c

HEADER = minishell.h

LINKERFLAG = -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(OBJ) $(MAIN) $(OBJ_LIB) $(OBJ_GNL) $(HEADER)
		@make -C ./libft
		@ar rcs $(NAME) $(OBJ) $(OBJ_LIB) $(OBJ_GNL)
		@gcc $(MAIN) $(NAME) $(LIBS) $(LIBFT) -o minishell
		@echo SUCCESS

%.o: %.c
		@gcc $(LINKERFLAG) $< -o $@

clean:
		@rm -f libft/libft.a
		@rm -f *.o
		@rm -f libft/*.o
		@rm -f get_next_line/*.o

fclean: clean
		@rm -f $(NAME)
		@rm -f minishell

re: fclean all