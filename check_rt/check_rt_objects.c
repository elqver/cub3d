/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:09:12 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:09:44 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

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
