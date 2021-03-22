/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:46:02 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 20:48:56 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

static int 	g_ambient_is_set;
static int 	g_camera_is_set;
static int	g_resolution_is_set;

static int	is_digit(char symb)
{
	if ('0' <= symb && symb <= '9')
	{
		printf("is digit TRUE\n");
		return (1);
	}
	printf("is digit FALSE, symb is %c\n", symb);
	return (0);
}

int			check_number(char **line)
{
	printf("check number from: %s\n", *line);
	while (**line == ' ')
		(*line)++;
	if (**line == '-' || **line == '+')
		(*line)++;
	if (!is_digit(**line))
	{
		printf("\n check_number fucked up\n");
		return (0);
	}
	while (is_digit(**line))
		(*line)++;
	if (**line != '.')
		return (1);
	(*line)++;
	while (is_digit(**line))
		(*line)++;
	return (1);
}

int			check_three_numbers(char **line)
{
	printf("check three numbers from: %s\n", *line);
	if (check_number(line))
		if (**line == ',')
		{
			(*line)++;
			if (check_number(line))
			{
				if (**line == ',')
				{
					(*line)++;
					if (check_number(line))
						return (1);
				}
			}
		}
	return (0);
}

int			check_empty_end(char **line)
{
	printf("check empty end: %s\n", *line);
	while (**line == ' ' || **line == '\n')
		(*line)++;
	if (**line != '\0')
	{
		printf("imposter char in the end of line with code: %d\n", **line);
		return (0);
	}
	printf("end was found correctly\n");
	return (1);
}

int			check_resolution(char **line)
{
	if (g_resolution_is_set == 1)
	{
		printf("resolution was set second time\n");
		return (0);
	}
	g_resolution_is_set = 1;
	printf("check resulution: %s\n", *line);
	if (check_number(line))
		if (check_number(line))
			if (check_empty_end(line))
				return (1);
	return (0);
}

int			check_ambient(char **line)
{
	if (g_ambient_is_set == 1)
	{
		printf("ambient was set second time\n");
		return (0);
	}
	g_ambient_is_set = 1;
	printf("check ambient: %s\n", *line);
	if (check_number(line))
		if (check_three_numbers(line))
			if (check_empty_end(line))
				return (1);
	printf("ambient is broken\n");
	return (0);
}

int			check_camera(char **line)
{
	g_camera_is_set = 1;
	printf("check camera: %s\n", *line);
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_number(line))
				if (check_empty_end(line))
					return (1);
	printf("camera is broken\n");
	return (0);
}

int			check_light(char **line)
{
	printf("check light: %s\n", *line);
	if (check_three_numbers(line))
		if (check_number(line))
			if (check_three_numbers(line))
				if (check_empty_end(line))
					return (1);
	printf("light is broken\n");
	return (0);
}

int			check_sphere(char **line)
{
	printf("check sphere: %s\n", *line);
	if (check_three_numbers(line))
		if (check_number(line))
			if (check_three_numbers(line))
				if (check_empty_end(line))
					return (1);
	printf("sphere is broken\n");
	return (0);
}

int			check_plane(char **line)
{
	printf("check plane: %s\n", *line);
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_three_numbers(line))
				if (check_empty_end(line))
					return (1);
	printf("plane is broken\n");
	return (0);
}

int			check_square(char **line)
{
	printf("check square: %s\n", *line);
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_number(line))
				if (check_three_numbers(line))
					if (check_empty_end(line))
						return (1);
	printf("square is broken\n");
	return (0);
}

int			check_cylinder(char **line)
{
	printf("check cylinder: %s\n", *line);
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_number(line))
				if (check_number(line))
					if (check_three_numbers(line))
						if (check_empty_end(line))
							return (1);
	printf("cylinder is broken\n");
	return (0);
}

int			check_triangle(char **line)
{
	printf("check triangle: %s\n", *line);
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_three_numbers(line))
				if (check_three_numbers(line))
					if (check_empty_end(line))
						return (1);
	printf("triangle is broken\n");
	return (0);
}

int			get_type_identifier(char **line)
{
	char first_char;
	char second_char;

	first_char = *((*line)++);
	second_char = *((*line)++);
	if (first_char == 'R')
		return (RESOLUTION);
	else if (first_char == 'A')
		return (AMBIENT);
	else if (first_char == 'l')
		return (LIGHT);
	else if (first_char == 's' && second_char == 'p')
		return (SPHERE);
	if (first_char == 's' && second_char == 'q')
		return (SQUARE);
	else if (first_char == 'p' && second_char == 'l')
		return (PLANE);
	else if (first_char == 'c' && second_char == 'y')
		return (CYLINDER);
	else if (first_char == 'c')
		return (CAMERA);
	else if (first_char == 't' && second_char == 'r')
		return (TRIANGLE);
	printf("wrong identifier\n");	
	return (0);
}

static int	check_empty_line(char *line)
{
	printf("check if line is empty\n");
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line == '\0')
	{
		printf("line is empty\n");
		return (1);
	}
	printf("line is not empty with symbol code: '%d'\n", *line);
	return (0);
}

int			check_line(char *line)
{
	int		identifier;

	if (check_empty_line(line))
		return (1);
	identifier = get_type_identifier(&line);
	if (identifier == RESOLUTION)
		return (check_resolution(&line));
	if (identifier == AMBIENT)
		return (check_ambient(&line));
	if (identifier == CAMERA)
		return (check_camera(&line));
	if (identifier == LIGHT)
		return (check_light(&line));
	if (identifier == SPHERE)
		return (check_sphere(&line));
	if (identifier == PLANE)
		return (check_plane(&line));
	if (identifier == SQUARE)
		return (check_square(&line));
	if (identifier == CYLINDER)
		return (check_cylinder(&line));
	if (identifier == TRIANGLE)
		return (check_triangle(&line));
	printf("\tline is broken\n");
	return (0);
}

int			check_rt_file(char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (get_next_line(fd, &line))
	{
		printf("\nline checking: %s\n", line);
		if (!check_line(line))
			return (0);
		printf("\nline is ok\n");
	}
	if (!g_resolution_is_set)
	{
		printf("resolution is not set\n");
		return (0);
	}
	if (!g_ambient_is_set)
	{
		printf("ambient is not set\n");
		return (0);
	}
	return (1);
}
