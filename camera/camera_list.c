/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:49:01 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 17:40:22 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void			append_to_camera_state_list(t_camera camera_state)
{
	t_camera_state_list *current_list_node;

	if (g_camera_state_list == NULL)
	{
		g_camera_state_list = (t_camera_state_list *)malloc(
												sizeof(t_camera_state_list));
		g_camera_state_list->next = NULL;
		g_camera_state_list->prev = NULL;
		g_camera_state_list->camera_state = camera_state;
		return ;
	}
	current_list_node = g_camera_state_list;
	while (current_list_node->next != NULL)
		current_list_node = current_list_node->next;
	current_list_node->next = (t_camera_state_list *)malloc(
												sizeof(t_camera_state_list));
	current_list_node->next->next = NULL;
	current_list_node->next->prev = current_list_node;
	current_list_node->next->camera_state = camera_state;
}

void			loop_camera_state_list(void)
{
	t_camera_state_list *current_list_node;

	current_list_node = g_camera_state_list;
	while (current_list_node->next != NULL)
		current_list_node = current_list_node->next;
	g_camera_state_list->prev = current_list_node;
	current_list_node->next = g_camera_state_list;
}

void			swap_to_next_camera_state(void)
{
	g_camera_state_list->camera_state = g_camera;
	g_camera_state_list = g_camera_state_list->next;
	g_camera = g_camera_state_list->camera_state;
}

void			swap_to_prev_camera_state(void)
{
	g_camera_state_list->camera_state = g_camera;
	g_camera_state_list = g_camera_state_list->next;
	g_camera = g_camera_state_list->camera_state;
}
