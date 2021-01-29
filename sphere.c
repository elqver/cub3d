/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 00:58:02 by skern             #+#    #+#             */
/*   Updated: 2021/01/30 02:11:01 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "object3d.h"
#include <math.h>

typedef struct	s_sphere_data
{
	t_3d	center;
	float	radius;
	int		color;
}				t_sphere_data;

static int	ray_sphere_intersect(const t_sphere_data *data,
									s_3d ray_start_point,
									s_3d ray_direction,
									s_3d *intersection_point)
{
	float	a;
	float	b;
	float	c;
	float	D;

	a = dot_product(ray_direction, ray_direction);
	b = 2 * (dot_product(ray_direction, ray_start_point - data->center));
	c = dot_product(3d_difference(ray_start_point, data->center),
					3d_difference(ray_start_point, data->center))
		- data->radius * data->radius;

	D = b * b - 4 * a * c;

	if (D < 0)
	{
		return (-1);
	}
}

static int	get_sphere_color(t_sphere_data *data, s_3d intersection_point)
{
	return (data->color);
}	

t_object3d	*new_sphere(s_3d center, float radius, int color)
{
	t_object3d *sphere = (* t_object3d)malloc(sizeof(t_object3d));
	if (sphere == NULL)
		return (NULL);
	data = (* t_sphere_data)malloc(sizeof(t_sphere_data));
	if (data == NULL)
	{
		free(sphere);
		return (NULL);
	}
	sphere.data = data;	

}
