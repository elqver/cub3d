/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:49:01 by skern             #+#    #+#             */
/*   Updated: 2021/03/20 15:30:59 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "quaternion.h"

t_camera		create_camera_FOV(float FOV)
{
	t_camera	res;
	t_quat		zero_quaternion;

	zero_quaternion = t_quat_t_3d(t_3d_f(0, 0, 0));
	res.displacement = t_3d_f(0, 0, 0);
	res.rotation = zero_quaternion;
	res.rotation.a = 1;
	res.FOV = FOV;
	return (res);
}

static void		move_camera(t_3d base_direction, float distance)
{
	t_3d	tmp;

	tmp = t_3d_scalar_mul(t_3d_unit(t_3d_t_quat(t_quat_rotate(g_camera.rotation, base_direction))), distance);
	g_camera.displacement = t_3d_sum(g_camera.displacement, tmp);
}

void			move_camera_forward(float distance)
{
	move_camera(t_3d_f(0, 0, -1), distance);
}

void			move_camera_backward(float distance)
{
	move_camera(t_3d_f(0, 0, 1), distance);
}

void			move_camera_left(float distance)
{
	move_camera(t_3d_f(-1, 0, 0), distance);
}

void			move_camera_right(float distance)
{
	move_camera(t_3d_f(1, 0, 0), distance);
}

void			move_camera_up(float distance)
{
	move_camera(t_3d_f(0, 1, 0), distance);
}

void			move_camera_down(float distance)
{
	move_camera(t_3d_f(0, -1, 0), distance);
}

static void		rotate_camera(float angle, t_3d base_vector)
{
	t_quat	upd_quat;

	base_vector = t_3d_t_quat(t_quat_rotate(g_camera.rotation, base_vector));
	upd_quat = t_quat_set_rotation(angle, base_vector);
	g_camera.rotation = t_quat_compose_rotation(g_camera.rotation, upd_quat);
}

void			roll_camera(float	angle)
{
	t_3d	base_vector;

	base_vector.x = 0;
	base_vector.y = 0;
	base_vector.z = -1;

	rotate_camera(angle, base_vector);
}

void			pitch_camera(float angle)
{
	t_3d	base_vector;

	base_vector.x = 1;
	base_vector.y = 0;
	base_vector.z = 0;

	rotate_camera(angle, base_vector);
}

void			yaw_camera(float angle)
{
	t_3d	base_vector;

	base_vector.x = 0;
	base_vector.y = 1;
	base_vector.z = 0;

	rotate_camera(angle, base_vector);
}

t_3d			set_normal_on_camera(t_3d base_normal, t_3d point_position)
{
	if (t_3d_dot_product(base_normal, t_3d_difference(g_camera.displacement, point_position)) < 0)
		return (t_3d_scalar_mul(base_normal, -1));
	return (base_normal);
}

void				append_to_camera_state_list(t_camera camera_state)
{
	t_camera_state_list *current_list_node;

	if (g_camera_state_list == NULL)
	{
		g_camera_state_list = (t_camera_state_list *)malloc(sizeof(t_camera_state_list));
		g_camera_state_list->next = NULL;
		g_camera_state_list->prev = NULL;
		g_camera_state_list->camera_state = camera_state;
		return ;
	}
	current_list_node = g_camera_state_list;
	while (current_list_node->next != NULL)
		current_list_node = current_list_node->next;
	current_list_node->next = (t_camera_state_list *)malloc(sizeof(t_camera_state_list));
	current_list_node->next->next = NULL;
	current_list_node->next->prev = current_list_node;
	current_list_node->next->camera_state = camera_state;
}

void				loop_camera_state_list()
{
	t_camera_state_list *current_list_node;

	current_list_node = g_camera_state_list;
	while (current_list_node->next != NULL)
		current_list_node = current_list_node->next;
	g_camera_state_list->prev = current_list_node;
	current_list_node->next = g_camera_state_list;
}

void				swap_to_next_camera_state()
{
	g_camera_state_list->camera_state = g_camera;
	g_camera_state_list = g_camera_state_list->next;
	g_camera = g_camera_state_list->camera_state;
}

void				swap_to_prev_camera_state()
{
	g_camera_state_list->camera_state = g_camera;
	g_camera_state_list = g_camera_state_list->next;
	g_camera = g_camera_state_list->camera_state;
}
