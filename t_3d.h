/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_3d.h                                         	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 00:51:13 by skern             #+#    #+#             */
/*   Updated: 2021/03/04 21:30:41 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_3D_H
# define S_3D_H

typedef struct	s_3d
{
	float	x;
	float	y;
	float	z;
}				t_3d;

t_3d			t_3d_difference(t_3d a, t_3d b);
t_3d			t_3d_sum(t_3d a, t_3d b);
float			t_3d_dot_product(t_3d a, t_3d b);
t_3d			t_3d_corss_product(t_3d a, t_3d b);
t_3d			t_3d_scalar_mul(t_3d a, float b);
t_3d			t_3d_scalar_div(t_3d a, float b);
float			t_3d_modul(t_3d a);
t_3d			t_3d_f(float a, float b, float c);
t_3d			t_3d_unit(t_3d a);
t_3d			t_3d_color(int color);
int				color_t_3d(t_3d a);
t_3d			t_3d_pair_mul(t_3d a, t_3d b);

#endif
