/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:16:54 by skern             #+#    #+#             */
/*   Updated: 2021/03/17 19:07:23 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "object3d.h"

typedef struct  s_cylinder
{
    t_3d	center;
    t_3d	orientation;
    float	diameter;
    float 	height;
	int		color;
}               t_cylinder_data;

t_object3d	*new_cylinder(t_3d center, t_3d orientation, float diameter, float height, int color);

#endif
