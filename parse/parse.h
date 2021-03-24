/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:52:40 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:42:09 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../t_3d/t_3d.h"
# include "../quaternion/quaternion.h"
# include "../mlx_setup.h"
# include "../object3d/object3d.h"
# include "../object3d/cylinder.h"
# include "../object3d/plane.h"
# include "../object3d/sphere.h"
# include "../object3d/square.h"
# include "../object3d/triangle.h"
# include "../check_rt/check_rt.h"
# include "../gnl/get_next_line.h"
# include "../phong/phong.h"
# include "../light/light.h"

float		parse_number(char **str);
t_3d		parse_t_3d(char **str);
void		skip_till_digit(char **str);
void		parse_resloution(char **str);
t_3d		subpress_t_3d_color(t_3d color);
void		parse_ambient(char **str);
void		parse_camera(char **str);
void		parse_light(char **str);
void		parse_triangle(char **str);
void		parse_square(char **str);
void		parse_plane(char **str);
void		parse_sphere(char **str);
void		parse_cyliner(char **str);
int			check_empty_line(char *line);
void		parse_line(char *line);
void		parse_file(char *file_name);

#endif
