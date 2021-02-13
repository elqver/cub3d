/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_3d.h                                         	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 00:51:13 by skern             #+#    #+#             */
/*   Updated: 2021/02/13 16:33:19 by skern            ###   ########.fr       */
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
float			t_3d_modul(t_3d a);
t_3d			t_3d_f(float a, float b, float c);

#endif
