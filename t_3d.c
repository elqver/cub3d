/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_3d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:39:09 by skern             #+#    #+#             */
/*   Updated: 2021/02/10 14:30:56 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"


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
	
}
