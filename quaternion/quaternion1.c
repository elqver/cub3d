/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:09:45 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 17:09:34 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_quat			t_quat_unit(t_quat a)
{
	float	mag;

	mag = t_quat_magnitude(a);
	return (t_quat_4f(a.a / mag, a.x / mag, a.y / mag, a.z / mag));
}

t_quat			t_quat_set_rotation(float angle, t_3d axis)
{
	t_quat	res;

	res = t_quat_unit(t_quat_4f(0, axis.x, axis.y, axis.z));
	res = t_quat_4f(cos(angle / 2),
					sin(angle / 2) * res.x,
					sin(angle / 2) * res.y,
					sin(angle / 2) * res.z);
	return (res);
}

t_quat			t_quat_product(t_quat a, t_quat b)
{
	t_quat	res;

	res.a = a.a * b.a - a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.a * b.x + a.x * b.a + a.y * b.z - a.z * b.y;
	res.y = a.a * b.y + a.y * b.a + a.z * b.x - a.x * b.z;
	res.z = a.a * b.z + a.z * b.a + a.x * b.y - a.y * b.x;
	;
	return (res);
}

t_quat			t_quat_compose_rotation(t_quat first, t_quat second)
{
	return (t_quat_product(second, first));
}

t_quat			t_quat_rotate(t_quat rotation, t_3d target)
{
	return (t_quat_product(t_quat_product(rotation,
											t_quat_t_3d(target)),
							t_quat_conjugation(rotation)));
}
