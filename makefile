# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 18:19:02 by elahyani          #+#    #+#              #
#    Updated: 2020/10/27 16:20:15 by elahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

SRCS = cmds.c

SRC_GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

OBJ_GNL = $(SRC_GNL:.c=.o)

LIBFT = ./libft/libft.a

LINKERFLAG = -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_LIB) $(OBJ_GNL)
		@make -C ./libft
		@ar rcs $(NAME) $(OBJ) $(OBJ_LIB) $(OBJ_GNL)
		@gcc main.c $(NAME) $(LIBS) $(LIBFT) -o minishell

%.o: %.c
		@gcc $(LINKERFLAG) $< -o $@

clean:
		@rm -f *.o
		@rm -f libft/*.o
		@rm -f get_next_line/*.o

fclean: clean
		@rm -f $(NAME)
		@rm -f minishell

re: fclean all