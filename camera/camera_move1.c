/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:30:30 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:55:25 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void		move_camera(t_3d base_direction, float distance)
{
	t_3d	tmp;

	tmp = t_3d_scalar_mul(
				t_3d_unit(
					t_3d_t_quat(
						t_quat_rotate(g_camera.rotation,
										base_direction))),
				distance);
	g_camera.displacement = t_3d_sum(g_camera.displacement, tmp);
}

void			move_camera_forward(float distance)
{
	move_camera(t_3d_f(0, 0, -1), distance);
}

void			move_camera_backward(float distance)
{
	move_camera(t_3d_f(0, 0, 1), distance);
}
