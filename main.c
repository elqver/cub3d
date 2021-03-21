/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:04:13 by skern             #+#    #+#             */
/*   Updated: 2021/03/21 19:40:13 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include "mlx_setup.h"
#include <stdio.h>
#include <sphere.h>
#include <math.h>
#include "light.h"
#include "camera.h"
#include "object3d/object3d.h"
#include "object3d/sphere.h"
#include "object3d/cylinder.h"
#include "object3d/triangle.h"
#include "object3d/plane.h"
#include "object3d/square.h"
#include "phong/phong.h"
#include "parse/check_rt.h"
#include "bmp.h"

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void            my_mlx_pixel_put(int x, int y, int color)
{
    char    *dst;

    dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
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
	while (++j < WINDOW_HEIGHT)
	{
		i = -1;
		while (++i < WINDOW_WIDTH)
		{
			ray.x = (i - WINDOW_WIDTH / 2);
			ray.y = -(j - WINDOW_HEIGHT / 2);
			ray.z = -(WINDOW_WIDTH / (2 * tan(g_camera.FOV / 2)));
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
				my_mlx_pixel_put(i, j, (int)color);
			}
			else
				my_mlx_pixel_put(i, j, 0);
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
		render_screenshot("JOPA_TUPAYA.bmp");
	else
		return (0);

	printf("camera pos: %f, %f, %f\n", g_camera.displacement.x, g_camera.displacement.y, g_camera.displacement.z);
	printf("camera rot: %f, %f, %f, %f\n", g_camera.rotation.a, g_camera.rotation.x, g_camera.rotation.y, g_camera.rotation.z);

	draw_scene();
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

	/*
	add_obj_list(new_sphere(t_3d_f(-20, 30, -100), 30, 255 * 256 * 256 + 122 * 256 + 122));
	add_light_list(new_light(t_3d_f(-50, 100, -200), 0.3, GREEN));
	add_light_list(new_light(t_3d_f(-50, 100, -200), 0.3, BLUE));
	*/
	
	/*
	add_obj_list(new_sphere(t_3d_f(0, 0, -200), 50, GREEN));
	add_obj_list(new_cylinder(t_3d_f(0, 0, 0), t_3d_f(0, 1, 0), 2000, 100, RED));
	add_obj_list(new_plane(t_3d_f(0, -100, 0), t_3d_f(0, 1, 0), BLUE));
	add_obj_list(new_plane(t_3d_f(0, 0, -500), t_3d_f(0, 0, 1), WHITE));
	t_3d c1[] = {t_3d_f(100, 100, 100), t_3d_f(100, 150, 100), t_3d_f(100, 100, 150)};
	t_3d c2[] = {t_3d_f(50, 100, 100), t_3d_f(100, 150, 100), t_3d_f(100, 100, 150)};
	add_obj_list(new_triangle(c1, RED));
	add_obj_list(new_triangle(c2, GREEN));
	add_light_list(new_light(t_3d_f(0, 0, 0), 0.5, WHITE));
	add_light_list(new_light(t_3d_f(300, 300, 300), 0.1, RED));
	*/

	float jopa1[]	= {10, 100};
	add_obj_list(new_cylinder(t_3d_f(-20, 30, -100), t_3d_f(0, 1, 0), jopa1, WHITE));
	add_obj_list(new_cylinder(t_3d_f(-20, 30, -100), t_3d_f(0, 0, 1), jopa1, RED));
	t_3d c1[] = {t_3d_f(0, 0, -30), t_3d_f(50, 0, -30), t_3d_f(0, 50, -30)};
	add_obj_list(new_triangle(c1, RED));
	t_3d c2[] = {t_3d_f(50, 50, -30), t_3d_f(50, 0, -30), t_3d_f(0, 50, -30)};
	add_obj_list(new_triangle(c2, RED));
	add_obj_list(new_sphere(t_3d_f(0, 0, -50), 10, WHITE));
	add_obj_list(new_square(t_3d_f(0, 100, -80), t_3d_unit(t_3d_f(1, -1, 1)), 20, WHITE));
	add_light_list(new_light(t_3d_f(0, 0, 0), 0.1, WHITE));
	
	g_camera = create_camera_FOV(2 * 3.1415 / 6); 
	append_to_camera_state_list(g_camera);
	append_to_camera_state_list(g_camera);
	loop_camera_state_list();
	g_is_ambient_on = 1;
	g_is_diffuse_on = 1;
	g_ambient = 0.5;
}

int             main(void)
{
	if (check_rt_file("set_up.rt"))
	{
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT"); 
		img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									 &img.endian);
		set_up_scene();
		draw_scene();
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_key_hook(mlx_win, bind_camera_movements, &img);
		mlx_loop(mlx);
	}
	else
		printf("\nfile fucked up\n");
	append_to_camera_state_list(g_camera);
	append_to_camera_state_list(g_camera);
}
