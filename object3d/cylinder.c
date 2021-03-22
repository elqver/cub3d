/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:01:15 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 19:28:33 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object3d.h"
#include "../light.h"
#include "../t_3d.h"
#include "cylinder.h"
#include <math.h>
#include <stdlib.h>

static float	min_pos_number_if_possible(float a, float b)
{
	if (a > 0)
		if (((a < b) && (b > 0)) || b < 0)
			return (a);
	;
	return (b);
}

static int		check_cylinder_root(float root,
								const t_cylinder_data *data,
								t_3d ray_start_point,
								t_3d ray_direction)
{
	float	m;

	if (root < 0)
		return (0);
	m = t_3d_dot_product(
							ray_direction,
							t_3d_scalar_mul(data->orientation, root))
			+ t_3d_dot_product(
								t_3d_difference(
												ray_start_point,
												data->center),
								data->orientation);
	if (m >= -data->height / 2 && m <= data->height / 2)
		return (1);
	;
	return (0);
}

static float	calculate_distance(float c[4],
									const t_cylinder_data *data,
									t_3d ray_start_point,
									t_3d ray_direction)
{
	float	distance;

	distance = -1;
	if (check_cylinder_root(
							(-c[1] - sqrt(c[3])) / (2 * c[0]),
							data,
							ray_start_point,
							ray_direction))
		distance = ((-c[1] - sqrt(c[3])) / (2 * c[0]));
	else if (check_cylinder_root(
									(-c[1] + sqrt(c[3])) / (2 * c[0]),
									data,
									ray_start_point,
									ray_direction))
		distance = ((-c[1] + sqrt(c[3])) / (2 * c[0]));
	return (distance);
}

int				get_cylinder_intersect(const t_cylinder_data *data,
									t_3d ray_start_point,
									t_3d ray_direction,
									t_3d *intersection_point)
{
	float	c[4];
	float	distance;

	ray_direction = t_3d_unit(ray_direction);
	c[0] = t_3d_dot_product(ray_direction, ray_direction)
			- pow(t_3d_dot_product(ray_direction, data->orientation), 2);
	c[1] = 2 * (
			t_3d_dot_product(ray_direction,
							t_3d_difference(ray_start_point, data->center))
			- t_3d_dot_product(ray_direction, data->orientation)
			* t_3d_dot_product(t_3d_difference(ray_start_point, data->center),
												data->orientation));
	c[2] = t_3d_dot_product(t_3d_difference(ray_start_point, data->center),
			t_3d_difference(ray_start_point, data->center))
		- pow(data->diameter / 2, 2) - pow(t_3d_dot_product(t_3d_difference(
						ray_start_point, data->center), data->orientation), 2);
	c[3] = c[1] * c[1] - 4 * c[0] * c[2];
	if (c[3] < 0)
		return (0);
	distance = calculate_distance(c, data, ray_start_point, ray_direction);
	if (distance < 0)
		return (0);
	*intersection_point = t_3d_sum(ray_start_point,
									t_3d_scalar_mul(ray_direction, distance));
	return (1);
}

t_3d			base_cylinder_normal(t_cylinder_data *data,
										t_3d intersection_point)
{
	float	t;
	t_3d	pt;
	t_3d	surface_normal;

	t = t_3d_dot_product(
						t_3d_difference(
										intersection_point,
										data->center),
						t_3d_unit(data->orientation));
	pt = t_3d_sum(data->center, t_3d_scalar_mul(data->orientation, t));
	surface_normal = t_3d_unit(t_3d_difference(intersection_point, pt));
	;
	return (surface_normal);
}

int	static		get_cylinder_color(t_cylinder_data *data,
									t_3d intersection_point)
{
	return (data->color);
}

/*
** params[0] = diameter
** params[1] = height
*/

t_object3d		*new_cylinder(t_3d center,
								t_3d orientation,
								float params[2],
								int color)
{
	t_object3d		*cylinder;
	t_cylinder_data	*data;

	cylinder = (t_object3d *)malloc(sizeof(t_object3d));
	if (cylinder == NULL)
		return (NULL);
	data = (t_cylinder_data *)malloc(sizeof(t_cylinder_data));
	if (data == NULL)
	{
		free(cylinder);
		return (NULL);
	}
	data->center = center;
	data->orientation = orientation;
	data->diameter = params[0];
	data->height = params[1];
	data->color = color;
	cylinder->data = data;
	cylinder->intersect = get_cylinder_intersect;
	cylinder->get_color = get_cylinder_color;
	cylinder->get_normal_vector = base_cylinder_normal;
	;
	return (cylinder);
}
