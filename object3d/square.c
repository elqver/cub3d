/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:30:28 by skern             #+#    #+#             */
/*   Updated: 2021/03/18 17:40:11 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object3d.h"
#include "square.h"

static int	get_triangle_intersect(t_3d c[3], t_3d ray_start_point, t_3d ray_direction, t_3d *intersection_point)
{
	ray_direction = t_3d_unit(ray_direction);

	t_3d e1 = t_3d_difference(c[1], c[0]);
	t_3d e2 = t_3d_difference(c[2], c[0]);
	t_3d pvec = t_3d_cross_product(ray_direction, e2);
	float det = t_3d_dot_product(e1, pvec);
	if (det < 1e-8 && det > -1e-8)
		return 0;
	float inv_det = 1 / det;
	t_3d tvec = t_3d_difference(ray_start_point, c[0]);
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
	
	return (1);
}

int			get_square_intersect(const t_square_data *data,
								t_3d ray_start_point,
								t_3d ray_direction,
								t_3d *intersection_point)
{
	t_3d	target_c[3];

	target_c[0] = (data->c)[0];
	target_c[1] = (data->c)[1];
	target_c[2] = (data->c)[2];
	if (get_triangle_intersect(target_c, ray_start_point, ray_direction, intersection_point))
		return (1);
	target_c[1] = (data->c)[3];
	return (get_triangle_intersect(target_c, ray_start_point, ray_direction, intersection_point));
}

t_3d	base_square_normal(t_square_data *data, t_3d intersection_point)
{
	return (data->normal);
}

int		get_square_color(t_square_data *data, t_3d intersection_point)
{
	return (data->color);

}

t_object3d *new_square(t_3d center, t_3d normal, float side_size, int color)
{
	t_3d			base_dir_x;
	t_3d			base_dir_y;

	t_object3d		*square = (t_object3d *)malloc(sizeof(t_object3d));
	t_square_data 	*data = (t_square_data *)malloc(sizeof(t_square_data));
	base_dir_x = t_3d_cross_product(t_3d_f(0, 0, 1), normal);
	if (t_3d_modul(base_dir_x) == 0)
		base_dir_x = t_3d_cross_product(t_3d_f(0, 1, 0), normal);
	base_dir_y = t_3d_scalar_mul(t_3d_cross_product(t_3d_unit(base_dir_x), normal), side_size / 2);
	base_dir_x = t_3d_scalar_mul(base_dir_x, side_size / 2);
	(data->c)[0] = t_3d_sum(t_3d_sum(center, base_dir_x), base_dir_y);
	(data->c)[1] = t_3d_sum(t_3d_difference(center, base_dir_x), base_dir_y);
	(data->c)[2] = t_3d_difference(t_3d_difference(center, base_dir_x), base_dir_y);
	(data->c)[3] = t_3d_difference(t_3d_sum(center, base_dir_x), base_dir_y);
	data->normal = normal;
	data->color = color;
	square->data = data;
	square->intersect = get_square_intersect;
	square->get_color = get_square_color;
	square->get_normal_vector = base_square_normal;

	return (square);
}
