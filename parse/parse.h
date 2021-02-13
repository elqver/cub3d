/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:52:40 by skern             #+#    #+#             */
/*   Updated: 2021/02/13 16:04:06 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../camera.h"
# include "../object3d/object3d.h"
# include <stdio.h>
# include <stdlib.h>

int	parse_rt_file(char *rt_file, t_camera *camera, 
{
	int		fd;
	char	*line;

	if (fd = open(rt_file, O_RDONLY) < 0)
		return (0);
	while (get_next_line(fd, &line))
	{
		
	}
	
}

#endif
