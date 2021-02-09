# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skern <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 17:40:42 by skern             #+#    #+#              #
#    Updated: 2021/02/09 15:13:14 by skern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		= tmp.c object3d/sphere.c t_3d.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c 
			$(CC) -Imlx -Iobject3d -c $< -o ${<:.c=.o}

${NAME}:	$(OBJS)
			$(CC) -lmlx -framework OpenGL -framework AppKit ${OBJS} -o ${NAME}

all:		${NAME}

clean:		
			rm ${OBJS}

fclean:		clean
			rm ${NAME}

re:			fclean all
