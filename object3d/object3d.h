/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:33:03 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 14:28:38 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT3D_H
# define OBJECT3D_H

# include "../t_3d.h"
# include "stdlib.h"

typedef struct	s_object3d
{
	void	*data;

	int		(*intersect)();

	int		(*get_color)();

	t_3d	(*get_normal_vector)();

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
