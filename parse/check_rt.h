/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:59:24 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 20:14:35 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHECK_RT_H
# define CHECK_RT_H

# include <fcntl.h>
# include <stdlib.h>

# define RESOLUTION 1
# define AMBIENT 2
# define CAMERA 3
# define LIGHT 4
# define SPHERE 5
# define PLANE 6
# define SQUARE 7
# define CYLINDER 8
# define TRIANGLE 9

int			check_rt_file(char *file_name);
int			check_line(char *line);
int 		check_number(char **line);	
int 		check_three_numbers(char **line);
int 		check_empty_end(char **line);

int			check_resolution(char **line);
int			check_ambient(char **line);

int			check_camera(char **line);
int			check_light(char **line);
int			check_sphere(char **line);
int			check_plane(char **line);
int			check_square(char **line);
int			check_cylinder(char **line);
int			check_triangle(char **line);
int			get_type_identifier(char **line);

#endif
