/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:49:01 by skern             #+#    #+#             */
/*   Updated: 2021/02/10 16:57:02 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "t_quat.h"

t_camera		create_camera_FOV(float FOV)
{
	t_camera	res;
	t_3d		zero_vector;
	t_quat		zero_quaternion;

	zero_vector.x = 0;
	zero_vector.y = 0;
	zero_vector.z = 0;
	zero_quaternion = t_quat_t_3d(zero_vector);
	res.base_view_direction = zero_vector;
	res.displacement = zero_vector;
	res.rotation = zero_quaternion;
	res.FOV = FOV;
	return (res);
}

static void		rotate_camera(t_camera *camera, float angle, t_3d base_vector)
{
	t_quat	upd_quat;
	float	cosa;
	float	sina;

	cosa = cos(angle / 2);
	sina = sin(angle / 2);
	upd_quat = t_quat_t_3d(base_vector);
	upd_quat = t_quat_rotate(camera->rotation, upd_quat);
	upd_quat.a = cosa;
	upd_quat.x = upd_quat.x / sina;
	upd_quat.y = upd_quat.y / sina;
	upd_quat.z = upd_quat.z / sina;
	camera->rotation = t_quat_product(upd_quat, camera->rotation);

}

void			roll_camera(t_camera *camera, float	angle)
{
	t_3d	base_vector;

	base_vector.x = 1;
	base_vector.y = 0;
	base_vector.z = 0;

	rotate_camera(camera, angle, base_vector);
}


