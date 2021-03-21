/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:32:57 by skern             #+#    #+#             */
/*   Updated: 2021/03/21 19:46:14 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "object3d.h"

typedef struct	s_square_data
{
	t_3d		c[4];
	t_3d		normal;
	int			color;
}				t_square_data;

t_object3d		*new_square(t_3d center,
							t_3d normal,
							float side_size,
							int color);

#endif
