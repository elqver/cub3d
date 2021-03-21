/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:39:54 by skern             #+#    #+#             */
/*   Updated: 2021/03/20 16:15:16 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_SETUP_H
# define MLX_SETUP_H

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

void    		*mlx;
void    		*mlx_win;

typedef struct  s_data 
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

t_data  		img;

#endif
