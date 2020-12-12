# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 18:19:02 by elahyani          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2020/12/04 13:19:35 by ichejra          ###   ########.fr        #
=======
#    Updated: 2020/12/10 14:23:50 by elahyani         ###   ########.fr        #
>>>>>>> d333ef67e309afadb534b47da7ad6c9c2d49a2ea
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

SRCS =	execution.c \
		exp_cmd.c \
		cd_cmd.c \
		echo_cmd.c \
		env_cmd.c \
		pwd_cmd.c \
		unset_cmd.c \
		exec_child.c \
		debug.c \
		parsing/manag_list.c \
		parsing/parse_line.c \
		parsing/parse_list_line.c \
		parsing/parse_dollar.c \
		parsing/manag_stx_err.c \
		parsing/manag_quotes.c \
		parsing/split_cmds.c \
		# cmds.c \

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
		@rm -f parsing/*.o

fclean: clean
		@rm -f $(NAME)
		@rm -f minishell

re: fclean all