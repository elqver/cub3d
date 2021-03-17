/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:36:48 by skern             #+#    #+#             */
/*   Updated: 2021/03/17 16:09:49 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object3d.h"

typedef struct  s_plane
{
    t_3d	point;
    t_3d	normal;
	int		color;
}               t_plane_data;

t_object3d *new_plane(t_3d point, t_3d normal, int color);

#endif
