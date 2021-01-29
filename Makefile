# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skern <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 17:40:42 by skern             #+#    #+#              #
#    Updated: 2021/01/20 20:20:04 by skern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		= tmp.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

%.o:		%.c 
			$(CC) -Wall -Wextra -Werror -Imlx -c $< -o ${<:.c=.o}

${NAME}:	$(OBJS)
			$(CC) -lmlx -framework OpenGL -framework AppKit ${OBJS} 

all:		${NAME}
