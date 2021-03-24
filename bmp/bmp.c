/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skern <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:23:40 by skern             #+#    #+#             */
/*   Updated: 2021/03/24 21:41:14 by skern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

static void	*ft_calloc(size_t count, size_t size)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(count * size);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size * count)
		result[i++] = 0;
	return (void *)result;
}

void		bitmap_file_header(int padding_size, int fd)
{
	unsigned char	*file_header;
	int				file_size;

	file_header = ft_calloc(BMP_FILE_HEADER_SIZE, sizeof(unsigned char));
	file_size = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE
				+ (g_img.bits_per_pixel / 8 * g_window_width + padding_size)
				* g_window_height;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(BMP_FILE_HEADER_SIZE
										+ BMP_INFO_HEADER_SIZE);
	write(fd, file_header, BMP_FILE_HEADER_SIZE);
	free(file_header);
}

void		bitmap_info_header(int fd)
{
	unsigned char	*info_header;

	info_header = ft_calloc(BMP_INFO_HEADER_SIZE, sizeof(unsigned char));
	info_header[0] = (unsigned char)(BMP_INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(g_window_width);
	info_header[5] = (unsigned char)(g_window_width >> 8);
	info_header[6] = (unsigned char)(g_window_width >> 16);
	info_header[7] = (unsigned char)(g_window_width >> 24);
	info_header[8] = (unsigned char)(g_window_height);
	info_header[9] = (unsigned char)(g_window_height >> 8);
	info_header[10] = (unsigned char)(g_window_height >> 16);
	info_header[11] = (unsigned char)(g_window_height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(g_img.bits_per_pixel);
	write(fd, info_header, BMP_INFO_HEADER_SIZE);
	free(info_header);
}

void		render_screenshot(char *file_name)
{
	int				h;
	int				w;
	int				fd;
	int				padding_size;

	if (!(fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
	{
		printf("screenshot failed");
	}
	padding_size = 0;
	bitmap_file_header(padding_size, fd);
	bitmap_info_header(fd);
	h = g_window_height;
	while (h--)
	{
		w = 0;
		while (w < g_window_width)
		{
			write(fd, g_img.addr +
					(h * g_img.line_length + w * g_img.bits_per_pixel / 8), 4);
			w++;
		}
	}
	printf("\nDONESCRBMP");
	close(fd);
}
