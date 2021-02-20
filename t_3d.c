/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_3d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:39:09 by skern             #+#    #+#             */
/*   Updated: 2021/02/20 15:41:33 by skern            ###   ########.fr       */
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
