/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:12:07 by skern             #+#    #+#             */
/*   Updated: 2021/02/13 16:39:12 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object3d.h"

int				add_obj_list(t_object3d_list *list, t_object3d *obj)
{
	t_object3d_list	*current;

	current = list;
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

void			pop_obj_list(t_object3d_list *list)
{
	t_object3d_list *current;

	current = list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->prev->next = NULL;
	free(current);
}


