/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:24:43 by skern             #+#    #+#             */
/*   Updated: 2021/02/20 15:40:50 by skern            ###   ########.fr       */
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

void			move_camera_forward(t_camera *camera, float distance);
void			move_camera_backward(t_camera *camera, float distance);
void			move_camera_left(t_camera *camera, float distance);
void			move_camera_right(t_camera *camera, float distance);
void			move_camera_up(t_camera *camera, float distance);
void			move_camera_down(t_camera *camera, float distance);
void			roll_camera(t_camera *camera, float angle);
void			pitch_camera(t_camera *camera, float angle);
void			yaw_camera(t_camera *camera, float angle);
t_camera		create_camera_FOV(float FOV);
t_camera		create_camera();

