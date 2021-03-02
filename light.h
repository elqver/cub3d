/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 19:57:30 by skern             #+#    #+#             */
/*   Updated: 2021/03/02 16:12:02 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_3d.h"

typedef struct	s_light
{
	t_3d	position;
	float	ratio;
	int		color;
}				t_light;

typedef struct	s_light_list
{
	t_light				light;
	struct s_light_list	*next;
	struct s_light_list	*prev;
}				t_light_list;

t_light			new_light(t_3d position, float ratio, int color);
t_light_list	*g_light_list;
int				g_ambient;
int				add_light_list(t_light light);
void			pop_light_list();
int				color_t_3d(t_3d color);
t_3d			t_3d_color(int color);

