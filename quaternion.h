/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:56:14 by skern             #+#    #+#             */
/*   Updated: 2021/02/17 15:48:06 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "t_3d.h"

typedef struct	s_quaternion
{
	float	a;
	float	x;
	float	y;
	float	z;
}				t_quat;

t_quat			t_quat_4f(float a, float x, float y, float z);
t_quat			t_quat_t_3d(t_3d a);
t_3d			t_3d_t_quat(t_quat a);
float			t_quat_magnitude(t_quat a);
t_quat			t_quat_conjugation(t_quat a);
t_quat			t_quat_unit(t_quat a);
t_quat			t_quat_set_rotation(float angle, t_3d axis);
t_quat			t_quat_product(t_quat a, t_quat b);
t_quat			t_quat_compose_rotation(t_quat first, t_quat second);
t_quat			t_quat_rotate(t_quat rotation, t_3d target);

#endif
