/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:16:54 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 18:04:29 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "../light/light.h"
# include "../t_3d/t_3d.h"
# include "object3d.h"
# include <math.h>
# include <stdlib.h>

typedef struct	s_cylinder
{
	t_3d		center;
	t_3d		orientation;
	float		diameter;
	float		height;
	int			color;
}				t_cylinder_data;

t_object3d		*new_cylinder(t_3d center,
								t_3d orientation,
								float params[2],
								int color);

#endif
