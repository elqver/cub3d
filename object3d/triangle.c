/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:16:04 by skern             #+#    #+#             */
/*   Updated: 2021/03/17 20:12:59 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object3d.h"
#include "triangle.h"
#include "../t_3d.h"
#include <stdlib.h>

int		get_triangle_intersect(const t_triangle_data *data, t_3d ray_start_point, t_3d ray_direction, t_3d *intersection_point)
{
	ray_direction = t_3d_unit(ray_direction);

	t_3d e1 = t_3d_difference((data->c)[1], (data->c)[0]);
	t_3d e2 = t_3d_difference((data->c)[2], (data->c)[0]);
	t_3d pvec = t_3d_cross_product(ray_direction, e2);
	float det = t_3d_dot_product(e1, pvec);
	if (det < 1e-8 && det > -1e-8)
		return 0;
	float inv_det = 1 / det;
	t_3d tvec = t_3d_difference(ray_start_point, (data->c)[0]);
	float u = t_3d_dot_product(tvec, pvec) * inv_det;
	if (u < 0 || u > 1)
		return 0;
	t_3d qvec = t_3d_cross_product(tvec, e1);
	float v = t_3d_dot_product(ray_direction, qvec) * inv_det;
	if (v < 0 || u + v > 1)
		return 0;
	float distance = t_3d_dot_product(e2, qvec) * inv_det;
	
	intersection_point->x = ray_start_point.x + distance * ray_direction.x;
    intersection_point->y = ray_start_point.y + distance * ray_direction.y;
    intersection_point->z = ray_start_point.z + distance * ray_direction.z;
	printf("vse zaebis\n");
	
	return (1);
}

t_3d	base_triangle_normal(t_triangle_data *data, t_3d intersection_point)
{
	return (t_3d_unit(
				t_3d_cross_product(
					t_3d_difference((data->c)[2], (data->c)[0]),
					t_3d_difference((data->c)[1], (data->c)[0])
					)
				)
		   );
}

int		get_triangle_color(t_triangle_data *data, t_3d intersection_point)
{
	return (data->color);
}

t_object3d *new_triangle(t_3d c[3], int color)
{
	t_object3d *triangle = (t_object3d *)malloc(sizeof(t_object3d));
	if (triangle == NULL)
		return (NULL);
	t_triangle_data *data = (t_triangle_data *)malloc(sizeof(t_triangle_data));
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
	
	return (triangle);
}

