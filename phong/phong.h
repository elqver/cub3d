/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:23:02 by skern             #+#    #+#             */
/*   Updated: 2021/03/04 21:36:44 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHONG_H
# define PHONG_H

# include "../t_3d.h"
# include "../object3d/object3d.h"
# include "../camera.h"
# include "../light.h"


char	g_is_ambient_on;
char	g_is_diffuse_on;
char	g_is_specular_on;
float	g_ambient;

t_3d	phong_light_amplifier(const t_object3d *object, t_3d point_position);

#endif