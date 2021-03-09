/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:52:40 by skern             #+#    #+#             */
/*   Updated: 2021/03/09 18:01:56 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../camera.h"
# include "../object3d/object3d.h"
# include <stdio.h>
# include <stdlib.h>

int			check_rt_file(char *rt_file)
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
