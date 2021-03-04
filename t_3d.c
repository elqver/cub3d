/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_3d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:39:09 by skern             #+#    #+#             */
/*   Updated: 2021/03/04 21:59:18 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"
#include <math.h>

t_3d			t_3d_f(float a, float b, float c)
{
	t_3d	res;

	res.x = a;
	res.y = b;
	res.z = c;
	return (res);
}

t_3d			t_3d_unit(t_3d a)
{
	float mod;

	mod = t_3d_modul(a);
	if (mod != 0)
		return (t_3d_f(a.x / mod, a.y / mod, a.z / mod));
	return (a);
}

float			t_3d_modul(t_3d a)
{
	float	res;

	res = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	return (res);
}


t_3d			t_3d_difference(t_3d a, t_3d b)
{
	t_3d	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_3d			t_3d_sum(t_3d a, t_3d b)
{
	t_3d	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

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
	res.y = a.x * b.z - a.z * b.x;
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

	return (a);
}

t_3d			t_3d_color(int color)
{
	t_3d	res;

	res.x = color / 65536;
	res.y = color % 65536 / 256;
	res.z = color % 256;

	return (res);
}

int				color_t_3d(t_3d a)
{
	return ((int)a.x * 65536 + (int)a.y * 256 + (int)a.z);
}

t_3d			t_3d_pair_mul(t_3d a, t_3d b)
{
	a.x = a.x * b.x;
	a.y = a.y * b.y;
	a.z = a.z * b.z;
return (a);
}
