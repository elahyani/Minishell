# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 18:19:02 by elahyani          #+#    #+#              #
#    Updated: 2020/10/26 18:52:33 by elahyani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell.a

SRC_LIB = libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memccpy.c libft/ft_memmove.c libft/ft_memchr.c \
		libft/ft_memcmp.c libft/ft_strlen.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_strchr.c libft/ft_strrchr.c \
		libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_atoi.c libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c \
		libft/ft_isascii.c libft/ft_isprint.c libft/ft_toupper.c libft/ft_tolower.c libft/ft_calloc.c libft/ft_strdup.c \
		libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c \
		libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c

SRC_GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ_LIB = $(SRC_LIB:.c=.o)

OBJ_GNL = $(SRC_GNL:.c=.o)

LINKERFLAG = -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(OBJ_LIB) $(OBJ_GNL)
		@ar rcs $(NAME) $(OBJ_LIB) $(OBJ_GNL)
		@gcc main.c $(NAME) $(LIBS) -o minishell

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