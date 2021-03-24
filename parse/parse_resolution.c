/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:54:29 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:47:11 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_resloution(char **str)
{
	skip_till_digit(str);
	g_window_width = parse_number(str);
	if (g_window_width <= 100)
		g_window_width = 100;
	skip_till_digit(str);
	g_window_height = parse_number(str);
	if (g_window_height <= 100)
		g_window_height = 100;
}
