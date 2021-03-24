/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_3d_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:05:52 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:07:34 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"

float			t_3d_dot_product(t_3d a, t_3d b)
{
	float	res;

	res = a.x * b.x + a.y * b.y + a.z * b.z;
	return (res);
}

t_3d			t_3d_cross_product(t_3d a, t_3d b)
{
	t_3d	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_3d			t_3d_scalar_mul(t_3d a, float b)
{
	t_3d	res;

	res.x = a.x * b;
	res.y = a.y * b;
	res.z = a.z * b;
	return (res);
}

t_3d			t_3d_scalar_div(t_3d a, float b)
{
	a.x = a.x / b;
	a.y = a.y / b;
	a.z = a.z / b;
	;
	return (a);
}

t_3d			t_3d_color(int color)
{
	t_3d	res;

	res.x = color / 65536;
	res.y = color % 65536 / 256;
	res.z = color % 256;
	;
	return (res);
}
