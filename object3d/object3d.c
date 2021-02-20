/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:12:07 by skern             #+#    #+#             */
/*   Updated: 2021/02/20 19:51:27 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object3d.h"
#include <stdlib.h>

int				add_obj_list(t_object3d *obj)
{
	t_object3d_list	*current;

	if (obj == NULL)
		return (0);
	if (g_o3d_list == NULL)
	{
		g_o3d_list = (t_object3d_list *)malloc(sizeof(t_object3d_list));
		g_o3d_list->prev = NULL;
		g_o3d_list->next = NULL;
		g_o3d_list->obj = obj;
		return (1);
	}
	current = g_o3d_list;
	while (current->next != NULL)
		current = current->next;
	current->next = (t_object3d_list *)malloc(sizeof(t_object3d_list));
	if (current->next == NULL)
		return (0);
	current->next->obj = obj;
	current->next->next = NULL;
	current->next->prev = current;
	return (1);
}

void			pop_obj_list()
{
	t_object3d_list *current;

	if (g_o3d_list == NULL)
		return ;
	current = g_o3d_list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->prev->next = NULL;
	free(current);
}
