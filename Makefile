# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skern <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 17:40:42 by skern             #+#    #+#              #
#    Updated: 2021/03/24 20:57:42 by skern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		= bmp/bmp.c \
			  \
			  camera/camera_creations.c camera/camera_list.c \
			  camera/camera_move1.c camera/camera_move2.c \
			  camera/camera_rotate.c camera/set_normal_on_camera.c \
			  \
			  check_rt/check_rt_basic.c check_rt/check_rt_camera.c \
			  check_rt/check_rt_light.c check_rt/check_rt_main.c \
			  check_rt/check_rt_objects.c check_rt/check_rt_resolution.c \
			  \
			  gnl/get_next_line.c gnl/get_next_line_utils.c \
			  \
			  light/light.c \
			  \
			  object3d/object3d.c object3d/triangle.c object3d/square.c \
			  object3d/plane.c object3d/sphere.c object3d/cylinder.c \
			  \
			  parse/parse_basic_structures.c \
			  parse/parse_camera.c parse/parse_light.c parse/parse_main.c \
			  parse/parse_objects.c parse/parse_resolution.c \
			  parse/parse_utils.c \
			  \
			  phong/phong.c \
			  \
			  quaternion/quaternion1.c quaternion/quaternion2.c \
			  \
			  t_3d/t_3d_1.c t_3d/t_3d_2.c t_3d/t_3d_3.c \
			  \
			  ft_memcmp.c main.c

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
