/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:51:48 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 22:21:46 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_light(char **str)
{
	t_3d	postiton;
	t_3d	rgb_color;
	float	brightness;
	int		color;

	skip_till_digit(str);
	postiton = parse_t_3d(str);
	skip_till_digit(str);
	brightness = parse_number(str);
	if (brightness < 0 || brightness > 1)
		brightness = 1;
	skip_till_digit(str);
	rgb_color = parse_t_3d(str);
	rgb_color = subpress_t_3d_color(rgb_color);
	color = color_t_3d(rgb_color);
	add_light_list(new_light(postiton, brightness, color));
}

void	parse_ambient(char **str)
{
	float	amplifier;
	t_3d	color;

	skip_till_digit(str);
	amplifier = parse_number(str);
	if (amplifier > 1 || amplifier < 0)
		amplifier = 1;
	skip_till_digit(str);
	color = t_3d_scalar_div(subpress_t_3d_color(parse_t_3d(str)), 255);
	color = t_3d_scalar_mul(color, amplifier);
	g_ambient_amplifier = color;
	printf("g_ambient_amplifier = %f %f %f\n", color.x, color.y, color.z);
}
