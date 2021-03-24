/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_creations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:29:04 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 17:30:14 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_camera		create_camera_fov(float fov)
{
	t_camera	res;
	t_quat		zero_quaternion;

	zero_quaternion = t_quat_t_3d(t_3d_f(0, 0, 0));
	res.displacement = t_3d_f(0, 0, 0);
	res.rotation = zero_quaternion;
	res.rotation.a = 1;
	res.fov = fov;
	return (res);
}

t_camera		create_camera(t_3d displacement,
								t_quat rotation,
								float fov)
{
	t_camera	res;

	res.displacement = displacement;
	res.rotation = rotation;
	res.fov = fov / 57.29;
	;
	return (res);
}
