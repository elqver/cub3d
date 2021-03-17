/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:15:54 by skern             #+#    #+#             */
/*   Updated: 2021/03/17 19:07:14 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "object3d.h"

typedef struct	s_triangle_data
{
	t_3d	c[3];
	int		color;
}				t_triangle_data;

t_object3d *new_triangle(t_3d c[3], int color);

#endif
