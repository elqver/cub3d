/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:09:45 by skern             #+#    #+#             */
/*   Updated: 2021/02/10 17:02:02 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"
#include "quaternion.h"
#include <math.h>

t_quat			t_quat_4f(float a, float x, float y, float z)
{
	t_quat	res;

	res.a = a;
	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_quat			t_quat_t_3d(t_3d a)
{
	t_quat	res;

	res.a = 0;
	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
	return (res);
}

t_3d			t_3d_t_quat(t_quat a)
{
	t_3d	res;

	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
	return (res);
}

float			t_quat_magnitude(t_quat a)
{
	return (sqrt(a.a * a.a + a.x * a.x + a.y * a.y + a.z * a.z));
}

t_quat			t_quat_conjugation(t_quat a)
{
	return (t_quat_4f(a.a, -a.x, -a.y, -a.z));
}

t_quat			t_quat_unit(t_quat a)
{
	float	mag;

	mag = t_quat_magnitude(a);
	return (t_quat_4f(a.a, a.x/mag, a.y/mag, a.z/mag));
}

t_quat			t_quat_product(t_quat a, t_quat b)
{
	t_quat	res;

	res.a = a.a * b.a - a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.a * b.x + a.x * b.a + a.y * b.z - a.z * b.y;
	res.y = a.a * b.y + a.y * b.a + a.z * b.x - a.x * b.z;
	res.z = a.a * b.z + a.z * b.a + a.x * b.y - a.y * b.x;

	return (res);
}

t_quat			t_quat_rotate(t_quat rotation, t_quat target)
{
	return (t_quat_product(t_quat_product(rotation, target), t_quat_conjugation(rotation)));
}










