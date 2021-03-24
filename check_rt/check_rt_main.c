/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:08:31 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 22:46:49 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

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
		{
			free(line);
			return (0);
		}
		free(line);
		printf("\nline is ok\n");
	}
	free(line);
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
