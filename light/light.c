/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:22:39 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 13:45:17 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include <stdlib.h>

t_light			new_light(t_3d position, float ratio, int color)
{
	t_light	res;

	res.position = position;
	res.ratio = ratio;
	res.color = color;
	;
	return (res);
}

int				add_light_list(t_light light)
{
	t_light_list *current;

	if (g_light_list == NULL)
	{
		g_light_list = (t_light_list *)malloc(sizeof(t_light_list));
		g_light_list->next = NULL;
		g_light_list->prev = NULL;
		g_light_list->light = light;
		return (1);
	}
	current = g_light_list;
	while (current->next != NULL)
		current = current->next;
	current->next = (t_light_list *)malloc(sizeof(t_light_list));
	current->next->next = NULL;
	current->next->prev = current;
	current->next->light = light;
	return (1);
}

void			pop_light_list(void)
{
	t_light_list *current;

	if (g_light_list == NULL)
		return ;
	current = g_light_list;
	while (current->next != NULL)
		current = current->next;
	current->prev->next = NULL;
	free(current);
}
