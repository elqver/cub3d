/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:02:40 by skern             #+#    #+#             */
/*   Updated: 2021/02/17 19:37:15 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <sphere.h>
#include <math.h>
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

int             main(void)
{
    void    		*mlx;
    void    		*mlx_win;
	t_object3d_list	*obj_list;
    t_data  		img;

	t_quat a;
	t_quat b;
	t_quat c;

	printf("I AM HERE\n");
	a = t_quat_4f(0, 0, 0, 0);
	b = t_quat_4f(0.4, sqrt(1/3), sqrt(1/3), sqrt(1/3));
	c = t_quat_4f(1, 0, 0, 0);

	t_quat d = t_quat_compose_rotation(a, b);
	printf("%f, %f, %f, %f\n", d.a, d.x, d.y, d.z);
	d = t_quat_compose_rotation(c, b);
	printf("%f, %f, %f, %f\n", d.a, d.x, d.y, d.z);

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

	t_camera camera = create_camera_FOV(M_PI / 3);
	obj_list = (t_object3d_list *)malloc(sizeof(t_object3d_list));
	t_object3d *sphere = new_sphere(t_3d_f(-10, 0, 90), 15, 255 * 255 * 255);
	obj_list->next = NULL;
	obj_list->prev = NULL;
	obj_list->obj = sphere;
	sphere = new_sphere(t_3d_f(10, 0, 90), 20, 250 * 255 * 255 + 100 * 255 + 100);
	add_obj_list(obj_list, sphere);

	roll_camera(&camera, 0.3);
	//pitch_camera(&camera, -0.3);
	//yaw_camera(&camera, 0.3);

	draw_scene(camera, obj_list, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    mlx_loop(mlx);
}
