/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:43:10 by skern             #+#    #+#             */
/*   Updated: 2021/03/17 11:19:25 by skern            ###   ########.fr       */
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

#endif
