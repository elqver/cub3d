/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:49:01 by skern             #+#    #+#             */
/*   Updated: 2021/02/17 19:26:12 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "quaternion.h"

t_camera		create_camera_FOV(float FOV)
{
	t_camera	res;
	t_3d		zero_vector;
	t_quat		zero_quaternion;

	zero_vector.x = 0;
	zero_vector.y = 0;
	zero_vector.z = 0;
	zero_quaternion = t_quat_t_3d(zero_vector);
	res.displacement = zero_vector;
	res.rotation = zero_quaternion;
	res.rotation.x = 1;
	res.rotation.a = 0.001;
	res.FOV = FOV;
	return (res);
}

static void		rotate_camera(t_camera *camera, float angle, t_3d base_vector)
{
	t_quat	upd_quat;

	upd_quat = t_quat_set_rotation(angle, base_vector);
	camera->rotation = t_quat_compose_rotation(camera->rotation, upd_quat);
}

void			roll_camera(t_camera *camera, float	angle)
{
	t_3d	base_vector;

	base_vector.x = 0;
	base_vector.y = 0;
	base_vector.z = 1;

	rotate_camera(camera, angle, base_vector);
}

int				pitch_camera(t_camera *camera, float angle)
{
	t_3d	base_vector;

	base_vector.x = -1;
	base_vector.y = 0;
	base_vector.z = 0;

	rotate_camera(camera, angle, base_vector);
}

int				yaw_camera(t_camera *camera, float angle)
{
	t_3d	base_vector;

	base_vector.x = 0;
	base_vector.y = -1;
	base_vector.z = 0;

	rotate_camera(camera, angle, base_vector);
}
