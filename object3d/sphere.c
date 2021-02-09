/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 00:58:02 by skern             #+#    #+#             */
/*   Updated: 2021/02/09 16:24:46 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "object3d.h"
#include "../t_3d.h"
#include <math.h>
#include <stdlib.h>

typedef struct	s_sphere_data
{
	t_3d	center;
	float	radius;
	int		color;
}				t_sphere_data;

static int	get_sphere_intersect(const t_sphere_data *data,
									t_3d ray_start_point,
									t_3d ray_direction,
									t_3d *intersection_point)
{
	float	a;
	float	b;
	float	c;
	float	D;
	float	distance;
	a = t_3d_dot_product(ray_direction, ray_direction);
	b = 2 * (t_3d_dot_product(ray_direction, t_3d_difference(ray_start_point, data->center)));
	c = t_3d_dot_product(t_3d_difference(ray_start_point, data->center),
					t_3d_difference(ray_start_point, data->center))
		- data->radius * data->radius;
	D = b * b - 4 * a * c;
	if (D < 0)
		return (0);
	distance = (-b - D) / (2 * a);
	intersection_point->x = ray_start_point.x + distance * ray_direction.x;
	intersection_point->y = ray_start_point.y + distance * ray_direction.y;
	intersection_point->z = ray_start_point.z + distance * ray_direction.z;
	return(1);
}

static int	get_sphere_color(t_sphere_data *data, t_3d intersection_point)
{
	(void )intersection_point;
	return (data->color);
}	

t_object3d	*new_sphere(t_3d center, float radius, int color)
{
	t_object3d *sphere = (t_object3d *)malloc(sizeof(t_object3d));
	if (sphere == NULL)
		return (NULL);
	t_sphere_data *data = (t_sphere_data *)malloc(sizeof(t_sphere_data));
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

	return(sphere);
}
