/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:08:48 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 17:09:39 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

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
