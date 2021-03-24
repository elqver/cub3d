/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_3d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:39:09 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:07:04 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"

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
