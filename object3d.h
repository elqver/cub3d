/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 00:51:13 by skern             #+#    #+#             */
/*   Updated: 2021/01/30 01:49:13 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	t_3d
{
	float	x;
	float	y;
	float	z;
}				s_3d;

s_3d			3d_difference(s_3d a, s_3d b)
{
	s_3d	res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

s_3d			3d_sum(s_3d a, s_3d b)
{
	s_3d	res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

float			dot_product(s_3d a, s_3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

s_3d			corss_product(s_3d a, s_3d b)
{
	s_3d	res;

	res.x = (a.y * b.z - a.z * b.y);
	res.y = (a.z * b.x - a.x * b.z);
	res.z = (a.x * b.y - a.y * b.x);

	return (res);
}	

typedef struct	t_object3d
{
	void	*data;

	int		(*intersect)(const void *data, 
							s_3d ray_start_point,
							s_3d ray_direction, 
							s_3d *intersection_point);

	int		(*get_color)(const void *data, s_3d intersection_point);

}				s_object3d;
