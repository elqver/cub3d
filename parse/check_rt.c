/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:46:02 by skern             #+#    #+#             */
/*   Updated: 2021/03/09 18:01:51 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

static int	is_digit(char symb)
{
	if ('0' <= symb && symb <= '9')
		return (1);
	return (0);
}

int 		check_number(char **line)
{
	while (**line == ' ')
		*line++;
	if (**line == '-' || **line == '+')
		*line++;
	if (!is_digit(**line))
		return (0);
	while (is_digit(**line))
		*line++;
	if (**line != '.')
		return (1);
	*line++;
	while (is_digit(**line))
		*line++;
	return (1);
}

int 		check_three_numbers(char **line)
{
	if (check_number(line))
		if (**line == ',')
		{
			*line++;
			if (check_number(line))
			{
				if (**line == ',')
					{
						*line++;
						if (check_number(line))
							return (1);
					}
			}
		}
	return (0);

}

int 		check_empty_end(char **line)
{
	while (**line == ' ')
		*line++;
	if (**line != '\n')
		return (0);
	return (1);
}

int			check_resolution(char **line)
{
	static char first_time = 1;

	if (!first_time)
	   return (0);	
	first_time = 0;
	if (check_number(line))
		if (check_number(line))
			if (check_empty_end(line))
				return (1);
}

int			check_ambient(char **line)
{
	static char first_time = 1;

	if (!first_time)
	   return (0);	
	if (check_number(line))
		if (check_three_numbers(line))
			if (check_empty_end(line))
				return (1);
	return (0);
}

int			check_camera(char **line)
{
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_number(line))
				if (check_empty_end(**line))
					return (1);
	return (0);
}

int			check_light(char **line)
{
	if (check_three_numbers(line))
		if (check_number(line))
			if (check_three_numbers(line))
				if (check_empty_end(line))
					return (1);
	return (0);
}

int			check_sphere(char **line)
{
	if (check_three_numbers(line))
		if (check_number(line))
			if (check_three_numbers(line))
				if (check_empty_end(line))
					return (1);
	return (0);
}

int			check_plane(char **line)
{
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_three_numbers(line))
				if (check_empty_end(line))
					return (1);
	return (0);
}

int			check_square(char **line)
{
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_number(line))
				if (check_three_numbers(line))
					if (check_empty_end(line))
						return (1);
	return (0);
}

int			check_cylinder(char **line)
{
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_number(line))
				if (check_number(line))
					if (check_three_numbers(line))
						if (check_empty_end(line))
							return (1);
	return (0);
}

int			check_triangle(char **line)
{
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_three_numbers(line))
				if (check_three_numbers(line))
					if (check_empty_end(line))
						return (1);
	return (0);
}

int			get_type_identifier(char **line)
{
	char first_char;
	char second_char;
	
	first_char = *(*line++);
	if (first_char == 'R')
		return (RESOLUTION);
	else if (first_char == 'A')
		return (AMBIENT);
	else if (first_char == 'l')
		return (LIGHT);
	else if (first_char == 's')
	{
		second_char = *(*line++);
		if (second_char == 'p')
			return (SPHERE);
		if (second_char == 'q')
			return (SQUARE);
	}
	else if (first_char == 'p')
	{
		second_char = *(*line++);
		if (second_char == 'l')
			return (PLANE);
	}
	else if (first_char == 'c')
	{
		second_char = *(*line++);
		if (second_char == 'y')
			return (CYLINDER);
		if (second_char == ' ')
			return (CAMERA);
	}
	else if (first_char == 't')
	{
		second_char = *(*line++);
		if (second_char == 'r')
			return (TRIANGLE);
	}
	return (0);
}

int			check_line(char *line)
{
	int		identifier;

	identifier = get_type_identifier(char &line);
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
	return (0);
}

