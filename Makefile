# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skern <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 17:40:42 by skern             #+#    #+#              #
#    Updated: 2021/03/18 17:34:43 by skern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		= main.c object3d/sphere.c light.c t_3d.c quaternion.c camera.c ft_memcmp.c object3d/object3d.c phong/phong.c parse/check_rt.c gnl/get_next_line.c gnl/get_next_line_utils.c object3d/cylinder.c object3d/plane.c object3d/triangle.c object3d/square.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c 
			$(CC) -Imlx -Iobject3d -c $< -o ${<:.c=.o} -g

${NAME}:	$(OBJS)
			$(CC) -lmlx -framework OpenGL -framework AppKit ${OBJS} -o ${NAME}

all:		${NAME}

clean:		
			rm ${OBJS}

fclean:		clean
			rm ${NAME}

re:			fclean all
