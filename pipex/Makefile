# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.de>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 14:44:47 by kaan              #+#    #+#              #
#    Updated: 2024/03/16 01:49:07 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra 

LIBS	=	./libraries/libft/libft.a

SRCS	=	pipex.c\
			utils.c\

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJS)
			make -C ./libraries/libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(PRINTF) -o $(NAME)

clean:
			make clean -C ./libraries/libft
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re
