/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:23:14 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 17:29:01 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"

static int		check_for_obstacles(t_3d first_point, t_3d second_point)
{
	t_object3d_list	*obj_node;
	float			existing_distance;
	t_3d			direction;
	t_3d			interim_point;

	obj_node = g_o3d_list;
	existing_distance = t_3d_modul(t_3d_difference(first_point, second_point));
	direction = t_3d_difference(second_point, first_point);
	while (obj_node != NULL)
	{
		if (obj_node->obj->intersect(obj_node->obj->data,
										first_point,
										direction,
										&interim_point))
			if (existing_distance > t_3d_modul(t_3d_difference(first_point,
																interim_point)))
				return (1);
		obj_node = obj_node->next;
	}
	return (0);
}

t_3d			get_diffuse_amplifier(const t_object3d *object,
										t_3d point_position)
{
	t_light_list	*light;
	float			scalar_diff_amp;
	t_3d			diff_amp;
	t_3d			normal;
	t_3d			out_point;

	diff_amp = t_3d_f(0, 0, 0);
	light = g_light_list;
	normal = object->get_normal_vector(object->data, point_position);
	normal = set_normal_on_camera(normal, point_position);
	out_point = t_3d_sum(point_position, t_3d_scalar_mul(normal, 0.001));
	while (light != NULL)
	{
		if (check_for_obstacles(light->light.position, out_point) == 0)
		{
			scalar_diff_amp = t_3d_dot_product(normal, t_3d_unit(
					t_3d_difference(light->light.position, point_position)));
			if (scalar_diff_amp > 0)
				diff_amp = t_3d_sum(diff_amp,
				t_3d_scalar_mul(t_3d_scalar_div(t_3d_color(light->light.color),
												255), scalar_diff_amp));
		}
		light = light->next;
	}
	return (diff_amp);
}

static float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

static t_3d		compress_amplifier(t_3d amplifier)
{
	amplifier.x = min(1, amplifier.x);
	amplifier.y = min(1, amplifier.y);
	amplifier.z = min(1, amplifier.z);
	;
	return (amplifier);
}

t_3d			phong_light_amplifier(const t_object3d *object,
										t_3d point_position)
{
	t_3d	resulted_amplifier;

	resulted_amplifier = t_3d_f(0, 0, 0);
	if (g_is_ambient_on)
		resulted_amplifier = t_3d_sum(resulted_amplifier, g_ambient_amplifier);
	if (g_is_diffuse_on)
		resulted_amplifier = t_3d_sum(resulted_amplifier,
										get_diffuse_amplifier(object,
															point_position));
	if (g_is_specular_on)
		;
	return (compress_amplifier(resulted_amplifier));
}
