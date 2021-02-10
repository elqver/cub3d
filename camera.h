/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:24:43 by skern             #+#    #+#             */
/*   Updated: 2021/02/10 15:31:36 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"
#include "t_quat.h"

typedef struct	s_camera
{
	t_3d	displacement;
	t_quat	rotation;
	float	FOV;
}				t_camera;

int				roll_camera(t_camera *camera);
int				pitch_camera(t_camera *camera);
int				yaw_camera(t_camera *camera);
t_camera		create_camera();
