/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:02:40 by skern             #+#    #+#             */
/*   Updated: 2021/03/02 16:12:55 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <sphere.h>
#include <math.h>
#include "light.h"
#include "camera.h"
#include "object3d/object3d.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1280

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


int				draw_scene(t_camera camera, t_object3d_list *obj_list, t_data *img)
{
	t_object3d_list	*current_node;
	t_object3d		*nearest_obj;
	t_3d			current_intersection_point;
	t_3d			nearest_intersection_point;
	t_3d			ray;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		while (i < WINDOW_WIDTH)
		{
			ray.x = (i - WINDOW_WIDTH / 2);
			ray.y = -(j - WINDOW_HEIGHT / 2);
			ray.z = (WINDOW_WIDTH / (2 * tan(camera.FOV / 2)));
			ray = t_3d_t_quat(t_quat_rotate(camera.rotation, ray));

			current_node = obj_list;
			nearest_obj = NULL;
			nearest_intersection_point = camera.displacement;
			while (current_node != NULL)
			{
				if ((current_node->obj)->intersect(current_node->obj->data,
										camera.displacement,
										ray,
										&current_intersection_point) == 1)
				{
					if ((t_3d_modul(t_3d_difference(camera.displacement, current_intersection_point)) < t_3d_modul(t_3d_difference(camera.displacement, nearest_intersection_point))
						||	
						!ft_memcmp(&nearest_intersection_point, &(camera.displacement), sizeof(t_3d)))
						&&
						t_3d_dot_product(ray, t_3d_difference(current_intersection_point, camera.displacement)) > 0
						)
					{
						nearest_obj = current_node->obj;
						nearest_intersection_point = current_intersection_point;
					}
				}
				current_node = current_node->next;
			}
			if (nearest_obj != NULL)
				my_mlx_pixel_put(img, i, j, nearest_obj->get_color(nearest_obj->data, nearest_intersection_point));
			else
				my_mlx_pixel_put(img, i, j, 0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

typedef struct	s_draw
{
	t_camera 		*camera;
	t_object3d_list *obj_list;
	t_data			*img;
	void			*mlx;
	void			*mlx_win;
}				t_draw;


int				bind_camera_movements(int keycode, t_draw *jopa)
{
	printf("/t/tkeycode is %d\n", keycode);


	if (keycode == 13)
		move_camera_forward(jopa->camera, 10);
	else if (keycode == 1)
		move_camera_backward(jopa->camera, 10);
	else if (keycode == 2)
		move_camera_right(jopa->camera, 10);
	else if (keycode == 0)
		move_camera_left(jopa->camera, 10);
	else if (keycode == 49)
		move_camera_up(jopa->camera, 10);
	else if (keycode == 257)
		move_camera_down(jopa->camera, 10);
	else if (keycode == 12)
		roll_camera(jopa->camera, -0.2);
	else if (keycode == 14)
		roll_camera(jopa->camera, 0.2);
	else if (keycode == 15)
		pitch_camera(jopa->camera, 0.2);
	else if (keycode == 3)
		pitch_camera(jopa->camera, -0.2);
	else if (keycode == 6)
		yaw_camera(jopa->camera, -0.2);
	else if (keycode == 8)
		yaw_camera(jopa->camera, 0.2);
	else
		return(0);

	draw_scene(*(jopa->camera), jopa->obj_list, jopa->img);
	mlx_put_image_to_window(jopa->mlx, jopa->mlx_win, jopa->img->img, 0, 0);

	return(1);
}

void			set_up_scene()
{
	add_obj_list(new_sphere(t_3d_f(-40, 0, -90), 15, 255 * 255 * 255));
	add_obj_list(new_sphere(t_3d_f(-20, 0, -90), 20, 250 * 255 * 255 + 100 * 255 + 100));
	add_light_list(new_light(t_3d_f(-25, 30, -45), 0.5, 0xffffffff));
}

int             main(void)
{
    void    		*mlx;
    void    		*mlx_win;
    t_data  		img;

	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

	set_up_scene();
	t_camera camera = create_camera_FOV(M_PI / 3);
	draw_scene(camera, g_o3d_list, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	t_draw jopa;
	jopa.camera = &camera;
	jopa.obj_list = g_o3d_list;
	jopa.img = &img;
	jopa.mlx = mlx;
	jopa.mlx_win = mlx_win;

	mlx_key_hook(mlx_win, bind_camera_movements, &jopa);

    mlx_loop(mlx);
}
