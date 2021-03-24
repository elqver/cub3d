/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:52:37 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 19:03:48 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ');
}

static int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static float	float_part(char **str)
{
	float	res;
	float	digit;

	if (**str != '.')
		return (0);
	(*str)++;
	res = 0;
	digit = 0.1;
	while (ft_isdigit(**str))
	{
		res += **str - '0';
		digit /= 10;
		(*str)++;
	}
	return (res);
}

float			parse_number(char **str)
{
	float		res;
	float		sign;

	res = 0;
	sign = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
	{
		res *= 10;
		res += **str - '0';
		(*str)++;
	}
	res += float_part(str);
	return (sign * res);
}

t_3d			parse_t_3d(char **str)
{
	float	a;
	float	b;
	float	c;
	t_3d	res;

	a = parse_number(str);
	(*str)++;
	b = parse_number(str);
	(*str)++;
	c = parse_number(str);
	;
	return (t_3d_f(a, b, c));
}
