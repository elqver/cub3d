/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:22:19 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:48:47 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ');
}

int			ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void		skip_till_digit(char **str)
{
	while (!(ft_isdigit(**str)) && **str != '-')
		(*str)++;
}

t_3d	subpress_t_3d_color(t_3d color)
{
	if (color.x > 255 || color.x < 0)
		color.x = 255;
	if (color.y > 255 || color.y < 0)
		color.y = 255;
	if (color.z > 255 || color.z < 0)
		color.z = 255;
	;
	return (color);
}
