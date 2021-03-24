/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:33:06 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 17:33:33 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void		rotate_camera(float angle, t_3d base_vector)
{
	t_quat	upd_quat;

	base_vector = t_3d_t_quat(t_quat_rotate(g_camera.rotation, base_vector));
	upd_quat = t_quat_set_rotation(angle, base_vector);
	g_camera.rotation = t_quat_compose_rotation(g_camera.rotation, upd_quat);
}

void			roll_camera(float angle)
{
	t_3d	base_vector;

	base_vector.x = 0;
	base_vector.y = 0;
	base_vector.z = -1;
	;
	rotate_camera(angle, base_vector);
}

void			pitch_camera(float angle)
{
	t_3d	base_vector;

	base_vector.x = 1;
	base_vector.y = 0;
	base_vector.z = 0;
	;
	rotate_camera(angle, base_vector);
}

void			yaw_camera(float angle)
{
	t_3d	base_vector;

	base_vector.x = 0;
	base_vector.y = 1;
	base_vector.z = 0;
	;
	rotate_camera(angle, base_vector);
}
