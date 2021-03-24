/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:04:13 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 23:38:30 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include "mlx_setup.h"
#include <stdio.h>
#include <sphere.h>
#include <math.h>
#include "light/light.h"
#include "camera/camera.h"
#include "object3d/object3d.h"
#include "object3d/sphere.h"
#include "object3d/cylinder.h"
#include "object3d/triangle.h"
#include "object3d/plane.h"
#include "object3d/square.h"
#include "phong/phong.h"
#include "parse/parse.h"
#include "check_rt/check_rt.h"
#include "bmp/bmp.h"

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void            my_mlx_pixel_put(int x, int y, int color)
{
    char    *dst;

    dst = g_img.addr + (y * g_img.line_length + x * (g_img.bits_per_pixel / 8));
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

int				draw_scene()
{
	t_object3d	*nearest_obj;
	t_3d		nearest_intersection_point;
	t_3d		ray;
	int			i;
	int			j;
	int			color;
	
	j = -1;
	while (++j < g_window_height)
	{
		i = -1;
		while (++i < g_window_width)
		{
			ray.x = (i - g_window_width / 2);
			ray.y = -(j - g_window_height / 2);
			ray.z = -(g_window_width / (2 * tan(g_camera.fov / 2)));
			ray = t_3d_t_quat(t_quat_rotate(g_camera.rotation, ray));
			find_nearest(ray, &nearest_obj, &nearest_intersection_point);
			if (nearest_obj != NULL)
			{
				//Fong amplifier for every chanel should be used here for shadowing
				color = nearest_obj->get_color(nearest_obj->data, nearest_intersection_point);
				color = color_t_3d(t_3d_pair_mul(t_3d_color(color), 
								   phong_light_amplifier(nearest_obj, 
														  nearest_intersection_point)));
				my_mlx_pixel_put(i, j, (int)color);
			}
			else
				my_mlx_pixel_put(i, j, 0);
		}
	}
	return (1);	
}

int				bind_camera_movements(int keycode, t_data *g_img)
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
		roll_camera(-0.31415);
	else if (keycode == 14)
		roll_camera(0.31415);
	else if (keycode == 15)
		pitch_camera(0.31415);
	else if (keycode == 3)
		pitch_camera(-0.31415);
	else if (keycode == 6)
		yaw_camera(0.31415);
	else if (keycode == 8)
		yaw_camera(-0.31415);

	else if (keycode == 34)
		g_is_ambient_on = !g_is_ambient_on;
	else if (keycode == 31)
		g_is_diffuse_on = !g_is_diffuse_on;

	else if (keycode == 46)
		swap_to_next_camera_state();
	else if (keycode == 45)
		swap_to_prev_camera_state();

	else if (keycode == 11)
		render_screenshot("miniRT.bmp");
	else
		return (0);

	printf("camera pos: %f, %f, %f\n", g_camera.displacement.x, g_camera.displacement.y, g_camera.displacement.z);
	printf("camera rot: %f, %f, %f, %f\n", g_camera.rotation.a, g_camera.rotation.x, g_camera.rotation.y, g_camera.rotation.z);

	draw_scene();
	mlx_put_image_to_window(g_mlx, g_mlx_win, g_img->img, 0, 0);

	return(1);
}

static int		ft_strlen(char *line)
{
	int	result;

	result = 0;
	while (line[result] != '\0')
		result++;
	return (result);
}

int				file_is_rt(char *file_name)
{
	int	file_name_len;

	file_name_len = ft_strlen(file_name);
	if (!ft_memcmp(&(file_name[file_name_len - 3]), ".rt", 3))
		return (1);
	return (0);
}

void			set_up_g(void)
{
	loop_camera_state_list();
	g_is_ambient_on = 1;
	g_is_diffuse_on = 1;
	g_mlx = mlx_init();
	g_camera = g_camera_state_list->camera_state;
	g_img.img = mlx_new_image(g_mlx, g_window_width, g_window_height);
	g_img.addr = mlx_get_data_addr(g_img.img,
									&g_img.bits_per_pixel,
									&g_img.line_length,
									&g_img.endian);
}

int             main(int argc, char **argv)
{
	if (argc == 2 || argc == 3)
	{
		if (!file_is_rt(argv[1]) || !check_rt_file(argv[1]))
		{
			printf("something wrong with configuration file\n");
			return (1);
		}
		parse_file(argv[1]);
		set_up_g();
		draw_scene();
		if (argc == 3)
			if (!ft_memcmp(argv[2], "--save", 6))
			{
				printf("making screenshot\n");
				render_screenshot("miniRT.bmp");
				return (0);
			}
		g_mlx_win = mlx_new_window(g_mlx, g_window_width, g_window_height, "miniRT"); 
		mlx_put_image_to_window(g_mlx, g_mlx_win, g_img.img, 0, 0);
		mlx_key_hook(g_mlx_win, bind_camera_movements, &g_img);
		mlx_loop(g_mlx);
	}
	printf("wrong number of arguments\n");
	return (1);
}
