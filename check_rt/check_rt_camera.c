/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:11:00 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:13:52 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

int			check_camera(char **line)
{
	g_camera_is_set = 1;
	printf("check camera: %s\n", *line);
	if (check_three_numbers(line))
		if (check_three_numbers(line))
			if (check_number(line))
				if (check_empty_end(line))
					return (1);
	printf("camera is broken\n");
	return (0);
}
