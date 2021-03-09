/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:02:40 by skern             #+#    #+#             */
/*   Updated: 2021/03/09 13:13:07 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //delete me later
#include <mlx.h>
#include <stdio.h>
#include <sphere.h>
#include <math.h>
#include "light.h"
#include "camera.h"
#include "object3d/object3d.h"
#include "phong/phong.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

int	ft_memcmp(const void *s1, const void *s2, size_t n);

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


int				check_is_nearest(t_3d current_intersection_point, t_3d nearest_intersection_point, t_3d ray)
{
	if ((t_3d_modul(t_3d_difference(g_camera.displacement, current_intersection_point)) < t_3d_modul(t_3d_difference(g_camera.displacement, nearest_intersection_point))
	||	
	!ft_memcmp(&nearest_intersection_point, &(g_camera.displacement), sizeof(t_3d)))
	&&
	t_3d_dot_product(ray, t_3d_difference(current_intersection_point, g_camera.displacement)) > 0)
		return (1);
	return (0);

}

void			find_nearest(t_3d ray, t_object3d **nearest_obj, t_3d *nearest_intersection_point)
{
	t_object3d_list	*current_node;
	t_3d			current_intersection_point;

	current_node = g_o3d_list;
	*nearest_obj = NULL;
	*nearest_intersection_point = g_camera.displacement;
	while (current_node != NULL)
	{
		if ((current_node->obj)->intersect(current_node->obj->data,
								g_camera.displacement,
								ray,
								&current_intersection_point) == 1)
		{
			if (check_is_nearest(current_intersection_point, *nearest_intersection_point, ray))
			{
				*nearest_obj = current_node->obj;
				*nearest_intersection_point = current_intersection_point;
			}
		}
		current_node = current_node->next;
	}
}

int				draw_scene(t_data *img)
{
	t_object3d	*nearest_obj;
	t_3d		nearest_intersection_point;
	t_3d		ray;
	int			i;
	int			j;
	int			color;
	
	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		i = -1;
		while (++i < WINDOW_WIDTH)
		{
			ray.x = (i - WINDOW_WIDTH / 2);
			ray.y = -(j - WINDOW_HEIGHT / 2);
			ray.z = (WINDOW_WIDTH / (2 * tan(g_camera.FOV / 2)));
			ray = t_3d_t_quat(t_quat_rotate(g_camera.rotation, ray));
			find_nearest(ray, &nearest_obj, &nearest_intersection_point);
			if (nearest_obj != NULL)
			{
				//Fong amplifier for every chanel should be used here for shadowing
				color = nearest_obj->get_color(nearest_obj->data, nearest_intersection_point);
				color = color_t_3d(t_3d_pair_mul(t_3d_color(color), 
								   phong_light_amplifier(nearest_obj, 
														  nearest_intersection_point
														)
								   				)
								  );
				my_mlx_pixel_put(img, i, j, (int)color);
			}
			else
				my_mlx_pixel_put(img, i, j, 0);
		}
	}
	return (1);	
}

int				bind_camera_movements(int keycode, t_data *img)
{
	printf("current keycode is %d\n", keycode);
	if (keycode == 13)
		move_camera_forward(10);
	else if (keycode == 1)
		move_camera_backward(10);
	else if (keycode == 2)
		move_camera_right(10);
	else if (keycode == 0)
		move_camera_left(10);
	else if (keycode == 49)
		move_camera_up(10);
	else if (keycode == 257)
		move_camera_down(10);
	else if (keycode == 12)
		roll_camera(-0.2);
	else if (keycode == 14)
		roll_camera(0.2);
	else if (keycode == 15)
		pitch_camera(0.2);
	else if (keycode == 3)
		pitch_camera(-0.2);
	else if (keycode == 6)
		yaw_camera(0.2);
	else if (keycode == 8)
		yaw_camera(-0.2);

	else if (keycode == 34)
		g_is_ambient_on = !g_is_ambient_on;
	else if (keycode == 31)
		g_is_diffuse_on = !g_is_diffuse_on;
	else
		return (0);

	draw_scene(img);
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);

	return(1);
}

void			set_up_scene()
{
	/*
	add_obj_list(new_sphere(t_3d_f(-40, 0, -90), 15, RED));
	add_obj_list(new_sphere(t_3d_f(-20, 0, -90), 20, RED));
	add_light_list(new_light(t_3d_f(-30, 30, -90), 1, WHITE));
	*/

	/*
	add_obj_list(new_sphere(t_3d_f(-20, 0, -100), 3, RED));
	add_obj_list(new_sphere(t_3d_f(20, 0, -100), 30, RED));
	add_light_list(new_light(t_3d_f(-50, 0, -100), 1, WHITE));
	*/

	add_obj_list(new_sphere(t_3d_f(-20, 0, -100), 5, 255 * 256 * 256 + 122 * 256 + 122));
	add_obj_list(new_sphere(t_3d_f(20, 0, -100), 30, WHITE));
	add_light_list(new_light(t_3d_f(-50, 0, -92), 0.3, GREEN));
	add_light_list(new_light(t_3d_f(-50, 0, -108), 0.3, BLUE));


	g_camera = create_camera_FOV(2 * 3.1415 / 3); 
	g_is_ambient_on = 1;
	g_is_diffuse_on = 1;
	g_ambient = 0.5;
}

int             main(void)
{
   t_data  		img;

	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT"); 
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

	set_up_scene();
	draw_scene(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_key_hook(mlx_win, bind_camera_movements, &img);

    mlx_loop(mlx);
}
