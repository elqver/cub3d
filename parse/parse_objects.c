/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:37:30 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:47:13 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_triangle(char **str)
{
	t_3d	c[3];
	t_3d	rgb_color;
	int		color;

	skip_till_digit(str);
	c[0] = parse_t_3d(str);
	skip_till_digit(str);
	c[1] = parse_t_3d(str);
	skip_till_digit(str);
	c[2] = parse_t_3d(str);
	skip_till_digit(str);
	rgb_color = subpress_t_3d_color(parse_t_3d(str));
	color = color_t_3d(rgb_color);
	add_obj_list(new_triangle(c, color));
}

void	parse_square(char **str)
{
	t_3d	center;
	t_3d	normal;
	t_3d	rgb_color;
	float	side_size;
	int		color;

	skip_till_digit(str);
	center = parse_t_3d(str);
	skip_till_digit(str);
	normal = t_3d_unit(parse_t_3d(str));
	skip_till_digit(str);
	side_size = parse_number(str);
	skip_till_digit(str);
	rgb_color = subpress_t_3d_color(parse_t_3d(str));
	color = color_t_3d(rgb_color);
	add_obj_list(new_square(center, normal, side_size, color));
}

void	parse_plane(char **str)
{
	t_3d	point;
	t_3d	normal;
	t_3d	rgb_color;
	int		color;

	skip_till_digit(str);
	point = parse_t_3d(str);
	skip_till_digit(str);
	normal = t_3d_unit(parse_t_3d(str));
	skip_till_digit(str);
	rgb_color = subpress_t_3d_color(parse_t_3d(str));
	color = color_t_3d(rgb_color);
	add_obj_list(new_plane(point, normal, color));
}

void	parse_sphere(char **str)
{
	t_3d	center;
	t_3d	rgb_color;
	float	radius;
	int		color;

	skip_till_digit(str);
	center = parse_t_3d(str);
	skip_till_digit(str);
	radius = (parse_number(str)) / 2;
	skip_till_digit(str);
	rgb_color = subpress_t_3d_color(parse_t_3d(str));
	color = color_t_3d(rgb_color);
	add_obj_list(new_sphere(center, radius, color));
}

void	parse_cyliner(char **str)
{
	t_3d	center;
	t_3d	orientation;
	float	params[2];
	int		color;

	skip_till_digit(str);
	center = parse_t_3d(str);
	skip_till_digit(str);
	orientation = t_3d_unit(parse_t_3d(str));
	params[0] = parse_number(str);
	if (params[0] <= 0)
		params[0] = 20;
	params[1] = parse_number(str);
	if (params[1] <= 0)
		params[1] = 100;
	color = color_t_3d(subpress_t_3d_color(parse_t_3d(str)));
	add_obj_list(new_cylinder(center, orientation, params, color));
}
