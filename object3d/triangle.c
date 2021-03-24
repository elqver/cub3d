/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:16:04 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:37:50 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

int			get_triangle_intersect(const t_triangle_data *data,
								t_3d ray_start_point,
								t_3d rd,
								t_3d *intersection_point)
{
	t_3d	e[4];
	float	dist;
	float	det;
	float	u;
	float	v;

	rd = t_3d_unit(rd);
	e[0] = t_3d_difference((data->c)[1], (data->c)[0]);
	e[1] = t_3d_difference((data->c)[2], (data->c)[0]);
	e[2] = t_3d_cross_product(rd, e[1]);
	det = t_3d_dot_product(e[0], e[2]);
	if (det == 0)
		return (0);
	det = 1 / det;
	e[3] = t_3d_difference(ray_start_point, (data->c)[0]);
	u = t_3d_dot_product(e[3], e[2]) * det;
	if (u < 0 || u > 1)
		return (0);
	e[2] = t_3d_cross_product(e[3], e[0]);
	v = t_3d_dot_product(rd, e[2]) * det;
	if (v < 0 || u + v > 1)
		return (0);
	dist = t_3d_dot_product(e[1], e[2]) * det;
	*intersection_point = t_3d_sum(ray_start_point, t_3d_scalar_mul(rd, dist));
	return (1);
}

t_3d		base_triangle_normal(t_triangle_data *data, t_3d intersection_point)
{
	return (t_3d_unit(
				t_3d_cross_product(
					t_3d_difference((data->c)[2], (data->c)[0]),
					t_3d_difference((data->c)[1], (data->c)[0]))));
}

int			get_triangle_color(t_triangle_data *data, t_3d intersection_point)
{
	return (data->color);
}

t_object3d	*new_triangle(t_3d c[3], int color)
{
	t_object3d		*triangle;
	t_triangle_data	*data;

	triangle = (t_object3d *)malloc(sizeof(t_object3d));
	if (triangle == NULL)
		return (NULL);
	data = (t_triangle_data *)malloc(sizeof(t_triangle_data));
	if (data == NULL)
	{
		free(triangle);
		return (NULL);
	}
	(data->c)[0] = c[0];
	(data->c)[1] = c[1];
	(data->c)[2] = c[2];
	data->color = color;
	triangle->data = data;
	triangle->intersect = get_triangle_intersect;
	triangle->get_color = get_triangle_color;
	triangle->get_normal_vector = base_triangle_normal;
	;
	return (triangle);
}
