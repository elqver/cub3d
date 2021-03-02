/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:24:43 by skern             #+#    #+#             */
/*   Updated: 2021/03/02 16:30:08 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"
#include "quaternion.h"
#include <math.h>

typedef struct	s_camera
{
	t_3d	displacement;
	t_quat	rotation;
	float	FOV;
}				t_camera;

t_camera		g_camera;
void			move_camera_forward(float distance);
void			move_camera_backward(float distance);
void			move_camera_left(float distance);
void			move_camera_right(float distance);
void			move_camera_up(float distance);
void			move_camera_down(float distance);
void			roll_camera(float angle);
void			pitch_camera(float angle);
void			yaw_camera(float angle);
t_camera		create_camera_FOV(float FOV);
t_camera		create_camera();

