/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:51:51 by skern             #+#    #+#             */
/*   Updated: 2021/03/22 14:01:20 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_SETUP_H
# define MLX_SETUP_H

int				g_window_width;
int				g_window_height;
void			*g_mlx;
void			*g_mlx_win;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

t_data			g_img;

#endif
