/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:04:08 by skern             #+#    #+#             */
/*   Updated: 2021/03/21 16:30:59 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx_setup.h"

typedef struct			s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					ll;
	int					en;
}						t_img;

void			render_screenshot();

#endif

