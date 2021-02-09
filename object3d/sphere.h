/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:43:10 by skern             #+#    #+#             */
/*   Updated: 2021/02/09 14:30:34 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "object3d.h"

typedef struct	s_sphere_data
{
	t_3d	center;
	float	radius;	
	int		color;
}				t_sphere_data;

t_object3d	*new_sphere(t_3d center, float radius, int color);
void		free_sphere(t_object3d *sphere);

#endif
