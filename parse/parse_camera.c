/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:51:07 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 18:51:40 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_camera(char **str)
{
	t_3d	camera_position;
	t_3d	camera_direction;
	t_quat	rotation;
	float	fov;

	skip_till_digit(str);
	camera_position = parse_t_3d(str);
	skip_till_digit(str);
	camera_direction = t_3d_unit(parse_t_3d(str));
	skip_till_digit(str);
	fov = parse_number(str);
	if (fov < 0 || fov > 180)
		fov = 60;
	rotation = t_quat_t_3d(t_3d_cross_product(t_3d_f(0, 0, -1),
												camera_direction));
	rotation.a = 1 + t_3d_dot_product(t_3d_f(0, 0, -1), camera_direction);
	if (t_3d_dot_product(t_3d_f(0, 0, -1), camera_direction) == -1)
		rotation.y = -1;
	rotation = t_quat_unit(rotation);
	append_to_camera_state_list(create_camera(camera_position, rotation, fov));
}
