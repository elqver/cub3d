/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:36:44 by skern             #+#    #+#             */
/*   Updated: 2021/03/17 14:34:00 by skern            ###   ########.fr       */
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
		if (a < b && b > 0 || b < 0)
			return (a);
	return (b);
}

static int	check_cylinder_root(float root, const t_cylinder_data *data, t_3d ray_start_point, t_3d ray_direction)
{
	if (root < 0)
		return (0);
	float m = t_3d_dot_product(ray_direction, t_3d_scalar_mul(data->orientation, root)) + t_3d_dot_product(t_3d_difference(ray_start_point, data->center), data->orientation);
	if (m >= -data->height / 2 && m <= data->height / 2)
		return (1);
	return (0);
}

int         get_cylinder_intersect(const t_cylinder_data *data, t_3d ray_start_point, t_3d ray_direction, t_3d *intersection_point)
{
    float 	a;
    float 	b;
    float 	c;
    float 	D;
    float 	distance;

	ray_direction = t_3d_unit(ray_direction);
    a = t_3d_dot_product(ray_direction, ray_direction) - pow(t_3d_dot_product(ray_direction,data->orientation),2);
    b = 2 * (t_3d_dot_product(ray_direction, t_3d_difference(ray_start_point, data->center)) - t_3d_dot_product(ray_direction,data->orientation) * t_3d_dot_product(t_3d_difference(ray_start_point, data->center), data->orientation));
    c = t_3d_dot_product(t_3d_difference(ray_start_point, data->center),
               t_3d_difference(ray_start_point, data->center))
        - pow(data->diameter / 2, 2) - pow(t_3d_dot_product(t_3d_difference(ray_start_point, data->center), data->orientation), 2);
	D = b * b - 4 * a * c;
    if (D < 0)
        return (0);
	distance = -1;
	if (check_cylinder_root((-b - sqrt(D)) / (2 * a), data, ray_start_point, ray_direction))
		distance = ((-b - sqrt(D)) / (2 * a));
	else if (check_cylinder_root((-b + sqrt(D)) / (2 * a), data, ray_start_point, ray_direction))
		distance = ((-b + sqrt(D)) / (2 * a));
    if (distance < 0)
        return (0);
    intersection_point->x = ray_start_point.x + distance * ray_direction.x;
    intersection_point->y = ray_start_point.y + distance * ray_direction.y;
    intersection_point->z = ray_start_point.z + distance * ray_direction.z;
    return(1);
}

// THERE IS WRONG LOGIC IN THIS FUNCTION
// FIX THIS LATER
t_3d base_cylinder_normal(t_cylinder_data *data, t_3d intersection_point)
{
	float t = t_3d_dot_product(t_3d_difference(intersection_point, data->center), t_3d_unit(data->orientation));
	t_3d pt = t_3d_sum(data->center, t_3d_scalar_mul(data->orientation, t));
	t_3d surface_normal = t_3d_unit(t_3d_difference(intersection_point, pt));

	return (surface_normal);
}

int	get_cylinder_color(t_cylinder_data *data, t_3d intersection_point)
{
	return (data->color);
}

t_object3d *new_cylinder(t_3d center, t_3d orientation, float diameter, float height, int color)
{
	t_object3d *cylinder = (t_object3d *)malloc(sizeof(t_object3d));
	if (cylinder == NULL)
		return (NULL);
	t_cylinder_data *data = (t_cylinder_data *)malloc(sizeof(t_cylinder_data));
	if (data == NULL)
	{
		free(cylinder);
		return (NULL);
	}
	data->center = center;
	data->orientation = orientation;
	data->diameter = diameter;
	data->height = height;
	data->color = color;
	cylinder->data = data;
	cylinder->intersect = get_cylinder_intersect;
	cylinder->get_color = get_cylinder_color;
	cylinder->get_normal_vector = base_cylinder_normal;

	return(cylinder);
}

