# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 14:44:47 by kaan              #+#    #+#              #
#    Updated: 2024/01/28 13:14:24 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INC	= inc/

SRC_DIR = src/

OBJ_DIR	= obj/

CC = gcc

FLAGS = -Wall -Wextra -Werror -I

RM = rm -f

AR	= ar rcs

SRC = $(SRC_DIR)ft_printf.c\
		$(SRC_DIR)ft_putchar_printf.c\
		$(SRC_DIR)ft_strlen_printf.c\
		$(SRC_DIR)ft_putstr_printf.c\
		$(SRC_DIR)ft_putnbr_printf.c\
		$(SRC_DIR)spec_handle_1.c\
		$(SRC_DIR)spec_handle_2.c\
		$(SRC_DIR)ft_puthex.c

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) .cache_exists

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
