/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:31:15 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:55:26 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void			move_camera_left(float distance)
{
	move_camera(t_3d_f(-1, 0, 0), distance);
}

void			move_camera_right(float distance)
{
	move_camera(t_3d_f(1, 0, 0), distance);
}

void			move_camera_up(float distance)
{
	move_camera(t_3d_f(0, 1, 0), distance);
}

void			move_camera_down(float distance)
{
	move_camera(t_3d_f(0, -1, 0), distance);
}
