/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:39:23 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 22:46:09 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_empty_line(char *line)
{
	printf("i am here on line: \"%s\"\n", line);
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

void		parse_line(char *line)
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

void		parse_file(char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		parse_line(line);
		free(line);
	}
	free(line);
}
