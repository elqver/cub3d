/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:24:43 by skern             #+#    #+#             */
/*   Updated: 2021/02/17 18:52:24 by skern            ###   ########.fr       */
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

void			roll_camera(t_camera *camera, float angle);
int				pitch_camera(t_camera *camera, float angle);
int				yaw_camera(t_camera *camera, float angle);
t_camera		create_camera_FOV(float FOV);
t_camera		create_camera();
