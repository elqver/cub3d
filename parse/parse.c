/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:52:37 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 22:02:01 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_3d.h"
#include "../quaternion.h"
#include "../mlx_setup.h"
#include "../object3d/object3d.h"
#include "../object3d/cylinder.h"
#include "../object3d/plane.h"
#include "../object3d/sphere.h"
#include "../object3d/square.h"
#include "../object3d/triangle.h"
#include "check_rt.h"
#include "../gnl/get_next_line.h"
#include "../phong/phong.h"

static int		ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ');
}

static int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static float	float_part(char **str)
{
	float	res;
	float	digit;

	if (**str != '.')
		return (0);
	(*str)++;
	res = 0;
	digit = 0.1;
	while (ft_isdigit(**str))
	{
		res += **str - '0';
		digit /= 10;
		(*str)++;
	}
	return (res);	
}

static float	parse_number(char **str)
{
	float		res;
	float		sign;

	res = 0;
	sign = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
	{
		res *= 10;
		res += **str - '0';
		(*str)++;
	}
	res += float_part(str);
	return (sign * res);
}

static t_3d		parse_t_3d(char **str)
{
	float	a;
	float	b;
	float	c;
	t_3d	res;

	a = parse_number(str);
	(*str)++;
	b = parse_number(str);
	(*str)++;
	c = parse_number(str);
	;
	return (t_3d_f(a, b, c));
}

static void		skip_till_digit(char **str)
{
	while (!(ft_isdigit(**str)))
		(*str)++;
}

void	parse_resloution(char **str)
{
	skip_till_digit(str);
	g_window_width = parse_number(str);
	if (g_window_width <= 100)
		g_window_width = 100;
	skip_till_digit(str);
	g_window_height = parse_number(str);
	if (g_window_height <= 100)
		g_window_height = 100;
}

static t_3d	subpress_t_3d_color(t_3d color)
{
	if (color.x > 255 || color.x < 0)
		color.x = 255;
	if (color.y > 255 || color.y < 0)
		color.y = 255;
	if (color.z > 255 || color.z < 0)
		color.z = 255;
	;
	return (color);
}

void		parse_ambient(char **str)
{
	float	amplifier;
	t_3d	color;

	skip_till_digit(str);
	amplifier = parse_number(str);
	if (amplifier > 1 || amplifier < 0)
		amplifier = 1;
	skip_till_digit(str);
	color = t_3d_scalar_div(subpress_t_3d_color(parse_t_3d(str)), 255);
	color = t_3d_scalar_mul(color, amplifier);
	g_ambient_amplifier = color;
}

void	parse_camera(char **str)
{
	t_3d	camera_position;
	t_3d	camera_direction;
	t_quat	rotation;
	float	fov;

	skip_till_digit(str);
	camera_position = parse_t_3d(str);
	skip_till_digit(str);
	camera_direction = t_3d_unit(parse_t_3d(str));
	skip_till_digit(str);
	fov = parse_number(str);
	if (fov < 0 || fov > 180)
		fov = 60;

	rotation = t_quat_t_3d(t_3d_cross_product(t_3d_f(0, 0, -1), 
												camera_direction));
	rotation.a = 1 + t_3d_dot_product(t_3d_f(0, 0, -1), camera_direction);
	if (t_3d_dot_product(t_3d_f(0, 0, -1), camera_direction) == -1)
		rotation.y = 1;
	rotation = t_quat_unit(rotation);
	append_to_camera_state_list(create_camera(camera_position, rotation, fov));
}

void	parse_light(char **str)
{
	t_3d	postiton;
	t_3d	rgb_color;
	float	brightness;
	int		color;

	skip_till_digit(str);
	postiton = parse_t_3d(str);
	skip_till_digit(str);
	brightness = parse_number(str);
	if (brightness < 0 || brightness > 1)
		brightness = 1;
	skip_till_digit(str);
	rgb_color = parse_t_3d(str);
	rgb_color = subpress_t_3d_color(rgb_color);
	color = color_t_3d(rgb_color);
	add_light_list(new_light(postiton, brightness, color));	
}

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

static int	check_empty_line(char *line)
{
	printf("i am here on line: \"%s\"\n", line);
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

void	parse_line(char *line)
{
	int		identifier;

	if (check_empty_line(line))
		return ;
	identifier = get_type_identifier(&line);
	if (identifier == RESOLUTION)
		parse_resloution(&line);
	else if (identifier == AMBIENT)
		parse_ambient(&line);
	else if (identifier == CAMERA)
		parse_camera(&line);
	else if (identifier == LIGHT)
		parse_light(&line);
	else if (identifier == SPHERE)
		parse_sphere(&line);
	else if (identifier == PLANE)
		parse_plane(&line);
	else if (identifier == SQUARE)
		parse_square(&line);
	else if (identifier == CYLINDER)
		parse_cyliner(&line);
	else if (identifier == TRIANGLE)
		parse_triangle(&line);
}

void	parse_file(char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line))
		parse_line(line);
}
