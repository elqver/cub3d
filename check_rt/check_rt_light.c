/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:10:09 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:10:45 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

int			check_light(char **line)
{
	printf("check light: %s\n", *line);
	if (check_three_numbers(line))
		if (check_number(line))
			if (check_three_numbers(line))
				if (check_empty_end(line))
					return (1);
	printf("light is broken\n");
	return (0);
}

int			check_ambient(char **line)
{
	if (g_ambient_is_set == 1)
	{
		printf("ambient was set second time\n");
		return (0);
	}
	g_ambient_is_set = 1;
	printf("check ambient: %s\n", *line);
	if (check_number(line))
		if (check_three_numbers(line))
			if (check_empty_end(line))
				return (1);
	printf("ambient is broken\n");
	return (0);
}
