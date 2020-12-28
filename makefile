# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 18:19:02 by elahyani          #+#    #+#              #
#    Updated: 2020/12/28 08:26:01 by elahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

SRCS =	parsing/manag_list.c \
		parsing/parse_line.c \
		parsing/parse_list_line.c \
		parsing/parse_dollar.c \
		parsing/manag_stx_err.c \
		parsing/manag_quotes.c \
		parsing/split_cmds.c \
		parsing/check_for_q.c \
		parsing/initializations.c \
		parsing/dollar_utils.c \
		srcs/builtins/exp_cmd.c \
		srcs/builtins/cd_cmd.c \
		srcs/builtins/echo_cmd.c \
		srcs/builtins/env_cmd.c \
		srcs/builtins/pwd_cmd.c \
		srcs/builtins/unset_cmd.c \
		srcs/builtins/exit_cmd.c \
		srcs/exec_child.c \
		srcs/cd_utils.c \
		srcs/export_utils.c \
		srcs/ft_free_all.c \
		srcs/errors.c \
		srcs/io_redir.c \
		srcs/get_cmd.c \
		srcs/check_cmd.c \
		srcs/get_cmd_utils.c \
		srcs/io_pipe_utils.c \

SRC_GNL = get_next_line/get_next_line.c

OBJ = $(SRCS:.c=.o)

OBJ_GNL = $(SRC_GNL:.c=.o)

LIBFT = ./libft/libft.a

MAIN = main.c

HEADER = ./includes/minishell.h

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
		@rm -f srcs/builtins/*.o
		@rm -f srcs/*.o
		@rm -f libft/*.o
		@rm -f get_next_line/*.o
		@rm -f parsing/*.o

fclean: clean
		@rm -f $(NAME)
		@rm -f minishell

re: fclean all