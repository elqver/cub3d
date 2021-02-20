/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:22:39 by skern             #+#    #+#             */
/*   Updated: 2021/02/20 20:41:14 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_light			new_light(t_3d position, float ratio, int color)
{
	t_light	res;

	res.position = position;
	res.ratio = ratio;
	res.color = color;
}

int				add_light_list(t_light light)
{
	t_light_list *current;

	if (light == NULL)
		return (0);
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
	current->next.light = light;
	return (1);
}

void			pop_light_list()
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

int				color_t_3d(t_3d color)
{
	return (color.x * 256 * 256 + color.y * 256 + color.z);
}

t_3d			t_3d_color(int color)
{
	t_3d	res;

	res.x = color / (256 * 256);
	if (res.x > 255)
		res. x = 255;
	res.y = color % (256 * 256) / (256); 
	if (res.y > 255)
		res.y = 255;
	res.z = color % (256);
	if (res.z > 255)
		res.z = 255;
	return (res);
}

