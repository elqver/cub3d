/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:04:08 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 17:15:51 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../mlx_setup.h"

# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40

void			render_screenshot();

#endif
