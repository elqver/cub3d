/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:28:35 by skern             #+#    #+#             */
/*   Updated: 2021/03/21 20:00:55 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object3d.h"
#include "plane.h"
#include <stdlib.h>

int			get_plane_intersect(const t_plane_data *data,
								t_3d ray_start_point,
								t_3d ray_direction,
								t_3d *intersection_point)
{
	float	tmp;
	float	t;
	t_3d	x;

	x = t_3d_difference(ray_start_point, data->point);
	tmp = t_3d_dot_product(ray_direction, data->normal);
	if (tmp == 0)
		return (0);
	t = -t_3d_dot_product(x, data->normal) / tmp;
	if (t < 0)
		return (0);
	*intersection_point = t_3d_sum(ray_start_point,
									t_3d_scalar_mul(ray_direction, t));
	return (1);
}

t_3d		base_plane_normal(t_plane_data *data, t_3d intersection_point)
{
	return (data->normal);
}

int			get_plane_color(t_plane_data *data, t_3d intersection_point)
{
	return (data->color);
}

t_object3d	*new_plane(t_3d point, t_3d normal, int color)
{
	t_object3d		*plane;
	t_plane_data	*data;

	plane = (t_object3d *)malloc(sizeof(t_object3d));
	if (plane == NULL)
		return (NULL);
	data = (t_plane_data *)malloc(sizeof(t_plane_data));
	if (data == NULL)
	{
		free(plane);
		return (NULL);
	}
	data->point = point;
	data->normal = normal;
	data->color = color;
	plane->data = data;
	plane->intersect = get_plane_intersect;
	plane->get_color = get_plane_color;
	plane->get_normal_vector = base_plane_normal;
	;
	return (plane);
}
