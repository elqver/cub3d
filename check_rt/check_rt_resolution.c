/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:14:03 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:14:16 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

int			check_resolution(char **line)
{
	if (g_resolution_is_set == 1)
	{
		printf("resolution was set second time\n");
		return (0);
	}
	g_resolution_is_set = 1;
	printf("check resulution: %s\n", *line);
	if (check_number(line))
		if (check_number(line))
			if (check_empty_end(line))
				return (1);
	return (0);
}
