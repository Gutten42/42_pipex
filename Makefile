# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 16:54:57 by vguttenb          #+#    #+#              #
#    Updated: 2021/12/01 19:51:42 by vguttenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a

SOURCES = test.c \
			get_paths.c \
			search_comm.c \
			exec.c \
			get_execord.c \
			output.c \
			

OBJS = $(SOURCES:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
 
$(LIBFT):
	make -sC ./libft

clean:
	
	make clean -sC ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -sC ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
