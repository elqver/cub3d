/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:02:40 by skern             #+#    #+#             */
/*   Updated: 2021/02/13 18:22:08 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <sphere.h>
#include <math.h>
#include "camera.h"
#include "object3d/object3d.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

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

int				take_next_ray(t_camera camera, int i, int j, t_3d *ray)
{

	if ((i == WINDOW_WIDTH - 1) && (j == WINDOW_HEIGHT - 1))
		return (0);

	ray->x = (i - WINDOW_WIDTH / 2);
	ray->y = -(j - WINDOW_HEIGHT / 2);
	ray->z = (WINDOW_WIDTH / (2 * tan(camera.FOV / 2)));

	*ray = t_3d_t_quat(t_quat_rotate(camera.rotation, t_quat_t_3d(*ray)));

	return(1);
}

int				draw_scene(t_camera camera, t_object3d_list *obj_list, t_data *img)
{
	t_object3d_list	*current_node;
	t_object3d		*nearest_obj;
	t_3d			current_intersection_point;
	t_3d			nearest_intersection_point;
	t_3d			current_ray;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while	(take_next_ray(camera, i, j, &current_ray))
	{	
		nearest_obj = NULL;
		current_node = obj_list;
		nearest_intersection_point = camera.displacement;
		while (current_node != NULL)
		{
			if ((current_node->obj)->intersect(current_node->obj->data,
										camera.displacement,
										current_ray,
										&current_intersection_point) == 1)
			{
				if (t_3d_modul(t_3d_difference(camera.displacement, current_intersection_point)) < 
					t_3d_modul(t_3d_difference(camera.displacement, nearest_intersection_point)) 
					|| 
					!ft_memcmp(&nearest_intersection_point, &(camera.displacement), sizeof(t_3d)))
				{
					nearest_obj = current_node->obj;
					nearest_intersection_point = current_intersection_point;
				}
			}
			current_node = current_node->next;
		}
		if (nearest_obj != NULL)	
			my_mlx_pixel_put(img, i, j, nearest_obj->get_color(nearest_obj->data, nearest_intersection_point));
		if (i == WINDOW_WIDTH - 1)
		{
			j++;
			i = 0;
		}
		else
			i++;
	}
}

int             main(void)
{
    void    		*mlx;
    void    		*mlx_win;
	t_object3d_list	*obj_list;
    t_data  		img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);



	t_camera camera = create_camera_FOV(M_PI / 3);
	obj_list = (t_object3d_list *)malloc(sizeof(t_object3d_list));
	t_object3d *sphere = new_sphere(t_3d_f(0, 5, 23), 5, 120 * 255 * 255 + 120 * 255 + 30);
	obj_list->next = NULL;
	obj_list->prev = NULL;
	obj_list->obj = sphere;
	sphere = new_sphere(t_3d_f(15, 5, 40), 14, 250 * 255 * 255 + 100 * 255 + 100);
	add_obj_list(obj_list, sphere);


	draw_scene(camera, obj_list, &img);
	

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
