/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:36:44 by skern             #+#    #+#             */
/*   Updated: 2021/03/13 21:59:35 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object3d.h"
#include "../light.h"
#include "../t_3d.h"
#include <math.h>
#include <stdlib.h>

typedef struct  s_cylinder
{
    t_3d	center;
    t_3d	orientation;
    float	diameter;
    float 	height;
	int		color
}               t_cylinder_data;

static float	min_pos_number_if_possible(float a, float b)
{
	if (a > 0)
		if (a < b && b > 0 || b < 0)
			return (a);
	return (b);
}

int         intersect_cylinder_data(const t_cylinder_data *data, t_3d ray_start_point, t_3d ray_direction, t_3d *intersection_point)
{
    float 	a;
    float 	b;
    float 	c;
    float 	D;
    float 	distance;
    float	m;

    a = t_3d_dot_product(ray_direction, ray_direction) - pow(t_3d_dot_product(ray_direction,data->orientation),2);
    b = 2 * (t_3d_dot_product(ray_direction, t_3d_difference(ray_start_point, data->center)) - t_3d_dot_product(ray_direction,data->orientation) * t_3d_dot_product(t_3d_difference(ray_start_point, data->center), data->orientation));
    c = t_3d_dot_product(t_3d_difference(ray_start_point, data->center),
               t_3d_difference(ray_start_point, data->center))
        - pow(data->diameter / 2, 2) - pow(t_3d_dot_product(t_3d_difference(ray_start_point, data->center), data->orientation), 2);
    D = b * b - 4 * a * c;
    if (D < 0)
        return (0);
    distance = min_pos_number_if_possible((-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a));
    if (distance < 0)
        return (0);

    m = t_3d_dot_product(ray_direction,t_3d_scalar_mul(data->orientation,distance)) + t_3d_dot_product(t_3d_difference(ray_start_point, data->center), data->orientation);
    if (m  < -data->height || m > data->height/2)
        return 0;
    intersection_point->x = ray_start_point.x + distance * ray_direction.x;
    intersection_point->y = ray_start_point.y + distance * ray_direction.y;
    intersection_point->z = ray_start_point.z + distance * ray_direction.z;
    return(1);
}

t_3d get_cylinder_data_normal(t_cylinder_data *cylinder, t_3d intersection_point)
{
    return (t_3d_unit(t_3d_difference(intersection_point, cylinder->center)));
}

int	get_sylinder_color(t_cylinder_data *data, t_3d intersection_point)
{
	return (data->color);
}

t_object3d *new_cylinder(t_3d center, t_3d orientation, float height, float diameter, int color)
{
    t_object3d *object;
    t_cylinder_data *cylinder;
    if ((cylinder = (t_cylinder_data *)malloc(sizeof(t_cylinder_data)))  == NULL)
        return (NULL);
    if((object = (t_object3d *)malloc(sizeof(t_object3d))) == NULL)
    {
        free(cylinder);
        return (NULL);
    }
    cylinder->orientation = orientation;
    cylinder->center = center;
    cylinder->height = height;
    cylinder->diameter = diameter;
    cylinder->color = color;
    object->data = cylinder;
    object->intersect = intersect_cylinder_data;
    object->get_normal_vector = get_cylinder_data_normal;
    return (object);
}
