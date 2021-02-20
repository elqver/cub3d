/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:49:01 by skern             #+#    #+#             */
/*   Updated: 2021/02/20 19:47:42 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "quaternion.h"

t_camera		create_camera_FOV(float FOV)
{
	t_camera	res;
	t_quat		zero_quaternion;

	zero_quaternion = t_quat_t_3d(t_3d_f(0, 0, 0));
	res.displacement = t_3d_f(0, 0, 0);
	res.rotation = zero_quaternion;
	res.rotation.x = -1;
	res.FOV = FOV;
	return (res);
}

t_camera		g_camera;

static void		move_camera(t_camera *camera, t_3d base_direction, float distance)
{
	t_3d	tmp;

	tmp = t_3d_scalar_mul(t_3d_unit(t_3d_t_quat(t_quat_rotate(camera->rotation, base_direction))), distance);
	camera->displacement = t_3d_sum(camera->displacement, tmp);
}

void			move_camera_forward(t_camera *camera, float distance)
{
	move_camera(camera, t_3d_f(0, 0, 1), distance);
}

void			move_camera_backward(t_camera *camera, float distance)
{
	move_camera(camera, t_3d_f(0, 0, -1), distance);
}

void			move_camera_left(t_camera *camera, float distance)
{
	move_camera(camera, t_3d_f(-1, 0, 0), distance);
}

void			move_camera_right(t_camera *camera, float distance)
{
	move_camera(camera, t_3d_f(1, 0, 0), distance);
}

void			move_camera_up(t_camera *camera, float distance)
{
	move_camera(camera, t_3d_f(0, 1, 0), distance);
}

void			move_camera_down(t_camera *camera, float distance)
{
	move_camera(camera, t_3d_f(0, -1, 0), distance);
}

static void		rotate_camera(t_camera *camera, float angle, t_3d base_vector)
{
	t_quat	upd_quat;

	base_vector = t_3d_t_quat(t_quat_rotate(camera->rotation, base_vector));
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

void			pitch_camera(t_camera *camera, float angle)
{
	t_3d	base_vector;

	base_vector.x = -1;
	base_vector.y = 0;
	base_vector.z = 0;

	rotate_camera(camera, angle, base_vector);
}

void			yaw_camera(t_camera *camera, float angle)
{
	t_3d	base_vector;

	base_vector.x = 0;
	base_vector.y = -1;
	base_vector.z = 0;

	rotate_camera(camera, angle, base_vector);
}
