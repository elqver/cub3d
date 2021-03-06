/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:43:10 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:24:56 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include <math.h>
# include <stdlib.h>
# include "object3d.h"
# include "../light/light.h"
# include "../t_3d/t_3d.h"

typedef struct	s_sphere_data
{
	t_3d		center;
	float		radius;
	int			color;
}				t_sphere_data;

t_object3d		*new_sphere(t_3d center, float radius, int color);

#endif
