/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:02:40 by skern             #+#    #+#             */
/*   Updated: 2021/02/10 14:36:36 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <sphere.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             main(void)
{

	/*
    void    *mlx;
    void    *mlx_win;
    t_data  img;
	int		i;
	int		j;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
    		my_mlx_pixel_put(&img, i, j++, 0x00FF0011);
		}
		i++;
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
*/	
	//create ray
	t_3d ray_direction;

	ray_direction.x = 0;
	ray_direction.y = 0;
	ray_direction.z = 1;

	t_3d ray_start_point;

	ray_start_point.x = 1;
	ray_start_point.y = 1;
	ray_start_point.z = 1;


	//create sphere
	
	int my_color;
	my_color = 8486530;	
	t_3d my_center;
	my_center.x = 1;
	my_center.y = 1;
	my_center.z = 7;
	float my_radius;
	my_radius = 3;
	t_object3d *my_sphere = new_sphere(my_center, my_radius, my_color);


	t_3d res_point;
	int res = my_sphere->intersect(my_sphere->data, ray_start_point, ray_direction, &res_point);


	printf("Res is %d:\nx = %f\ny = %f\nz = %f\n", res, res_point.x, res_point.y, res_point.z);
}
