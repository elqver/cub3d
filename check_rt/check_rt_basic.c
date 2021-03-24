/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:12:27 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 20:12:55 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_rt.h"

int			is_digit(char symb)
{
	if ('0' <= symb && symb <= '9')
	{
		printf("is digit TRUE\n");
		return (1);
	}
	printf("is digit FALSE, symb is %c\n", symb);
	return (0);
}

int			check_number(char **line)
{
	printf("check number from: %s\n", *line);
	while (**line == ' ')
		(*line)++;
	if (**line == '-' || **line == '+')
		(*line)++;
	if (!is_digit(**line))
	{
		printf("\n check_number fucked up\n");
		return (0);
	}
	while (is_digit(**line))
		(*line)++;
	if (**line != '.')
		return (1);
	(*line)++;
	while (is_digit(**line))
		(*line)++;
	return (1);
}

int			check_three_numbers(char **line)
{
	printf("check three numbers from: %s\n", *line);
	if (check_number(line))
		if (**line == ',')
		{
			(*line)++;
			if (check_number(line))
			{
				if (**line == ',')
				{
					(*line)++;
					if (check_number(line))
						return (1);
				}
			}
		}
	return (0);
}

int			check_empty_end(char **line)
{
	printf("check empty end: %s\n", *line);
	while (**line == ' ' || **line == '\n')
		(*line)++;
	if (**line != '\0')
	{
		printf("imposter char in the end of line with code: %d\n", **line);
		return (0);
	}
	printf("end was found correctly\n");
	return (1);
}
