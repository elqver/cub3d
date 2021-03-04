/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 19:57:30 by skern             #+#    #+#             */
/*   Updated: 2021/03/04 21:34:56 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
#define LIGHT_H

# include "t_3d.h"

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


//REPLACE ME LATER!
void    		*mlx;
void    		*mlx_win;


t_light			new_light(t_3d position, float ratio, int color);
t_light_list	*g_light_list;
int				add_light_list(t_light light);
void			pop_light_list();
int				color_t_3d(t_3d color);

#endif
