/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:33:03 by skern             #+#    #+#             */
/*   Updated: 2021/02/20 14:37:48 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT3D_H
# define OBJECT3D_H

# include "../t_3d.h"
# include "stdlib.h"

typedef struct	s_object3d
{
	void	*data;

	int		(*intersect)(const void *data,
							t_3d ray_start_point,
							t_3d ray_direction,
							t_3d *intersection_point);

	int		(*get_color)(const void *data, t_3d intersection_point);

	t_3d	(*get_normal_vector)(const void *data,
									const t_3d intersection_point);

}				t_object3d;

typedef struct	s_object3d_list
{
	t_object3d				*obj;
	struct s_object3d_list	*next;
	struct s_object3d_list	*prev;
}				t_object3d_list;

t_object3d_list	*g_o3d_list;
int				add_obj_list(t_object3d *obj);
void			pop_obj_list();

#endif
