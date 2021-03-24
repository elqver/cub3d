/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_normal_on_camera.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:36:12 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 17:36:49 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_3d			set_normal_on_camera(t_3d base_normal, t_3d point_position)
{
	if (t_3d_dot_product(base_normal,
							t_3d_difference(g_camera.displacement,
											point_position)) < 0)
		return (t_3d_scalar_mul(base_normal, -1));
	return (base_normal);
}
