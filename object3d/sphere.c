/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 00:58:02 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 22:32:57 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

static float	min_pos_number_if_possible(float a, float b)
{
	if (a > 0)
		if (((a < b) && (b > 0)) || b < 0)
			return (a);
	return (b);
}

static int		get_sphere_intersect(const t_sphere_data *data,
									t_3d ray_start_point,
									t_3d ray_direction,
									t_3d *intersection_point)
{
	float	c[4];
	float	distance;

	ray_direction = t_3d_unit(ray_direction);
	c[0] = t_3d_dot_product(ray_direction, ray_direction);
	c[1] = 2 * (t_3d_dot_product(ray_direction,
				t_3d_difference(ray_start_point, data->center)));
	c[2] = t_3d_dot_product(t_3d_difference(ray_start_point, data->center),
					t_3d_difference(ray_start_point, data->center))
		- data->radius * data->radius;
	c[3] = c[1] * c[1] - 4 * c[0] * c[2];
	if (c[3] < 0)
		return (0);
	distance = min_pos_number_if_possible((-c[1] - sqrt(c[3])) / (2 * c[0]),
											(-c[1] + sqrt(c[3])) / (2 * c[0]));
	if (distance < 0)
		return (0);
	*intersection_point = t_3d_sum(ray_start_point,
									t_3d_scalar_mul(ray_direction, distance));
	return (1);
}

static t_3d		base_sphere_normal(t_sphere_data *data, t_3d intersection_point)
{
	return (t_3d_unit(t_3d_difference(intersection_point, data->center)));
}

static int		get_sphere_color(t_sphere_data *data, t_3d intersection_point)
{
	return (data->color);
}

t_object3d		*new_sphere(t_3d center, float radius, int color)
{
	t_object3d		*sphere;
	t_sphere_data	*data;

	sphere = (t_object3d *)malloc(sizeof(t_object3d));
	if (sphere == NULL)
		return (NULL);
	data = (t_sphere_data *)malloc(sizeof(t_sphere_data));
	if (data == NULL)
	{
		free(sphere);
		return (NULL);
	}
	data->center = center;
	data->radius = radius;
	data->color = color;
	sphere->data = data;
	sphere->intersect = get_sphere_intersect;
	sphere->get_color = get_sphere_color;
	sphere->get_normal_vector = base_sphere_normal;
	;
	return (sphere);
}
