# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 16:54:57 by vguttenb          #+#    #+#              #
#    Updated: 2021/12/13 19:17:35 by vguttenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a

SOURCES = pipex.c \
			search_comm.c \
			exec.c \
			exec_manage.c \
			piping.c \
			get_rfd.c \
			err_msg.c \
			pipex_utils.c \
			

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
