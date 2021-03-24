/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_3d.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:02:33 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:05:43 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_3D_H
# define T_3D_H

# include <math.h>

typedef struct	s_3d
{
	float	x;
	float	y;
	float	z;
}				t_3d;

t_3d			t_3d_difference(t_3d a, t_3d b);
t_3d			t_3d_sum(t_3d a, t_3d b);
float			t_3d_dot_product(t_3d a, t_3d b);
t_3d			t_3d_cross_product(t_3d a, t_3d b);
t_3d			t_3d_scalar_mul(t_3d a, float b);
t_3d			t_3d_scalar_div(t_3d a, float b);
float			t_3d_modul(t_3d a);
t_3d			t_3d_f(float a, float b, float c);
t_3d			t_3d_unit(t_3d a);
t_3d			t_3d_color(int color);
int				color_t_3d(t_3d a);
t_3d			t_3d_pair_mul(t_3d a, t_3d b);

#endif
