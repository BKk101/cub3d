#include "./cub3d.h"

void	set_default_value(unsigned char header[])
{
	unsigned int	bi_size;
	unsigned int	bf_off_bits;
	unsigned short	bi_planes;

	bi_size = 40;
	bf_off_bits = 54;
	bi_planes = 1;
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 10, &bf_off_bits, 4);
	ft_memcpy(header + 14, &bi_size, 4);
	ft_memcpy(header + 26, &bi_planes, 2);
}

void	set_header(unsigned char *header, t_window win, int imgsize)
{
	unsigned short	bitcount;
	unsigned int	filesize;
	unsigned int	bi_size;
	unsigned int	bf_off_bits;
	unsigned short	bi_planes;

	bi_size = 40;
	bf_off_bits = 54;
	bi_planes = 1;
	bitcount = 24;
	filesize = 54 + imgsize;
	//set_default_value(header);
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 10, &bf_off_bits, 4);
	ft_memcpy(header + 14, &bi_size, 4);
	ft_memcpy(header + 26, &bi_planes, 2);
	ft_memcpy(header + 2, &filesize, 4);
	ft_memcpy(header + 18, &win.wid, 4);
	ft_memcpy(header + 22, &win.hei, 4);
	ft_memcpy(header + 28, &bitcount, 2);
	ft_memcpy(header + 34, &imgsize, 4);
}
/*
static int get_color(t_window *w, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(w->screen.ptr
			+ (4 * (int)w->size.x * ((int)w->size.y - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}
*/
void	set_pixels(unsigned char *buf, t_window win, unsigned int wid_bytes)
{
	int				i;
	int				j;
	int				tmp;

	i = -1;
	tmp = win.hei;
	while (++i < win.hei)
	{
		j = -1;
		--tmp;
		while (++j < win.wid)
		{
			buf[tmp * wid_bytes + j * 3] = (win.scene[i][j] & 0x0000ff) | (win.scene[i][j] & 0x00ff00) | (win.scene[i][j] & 0xff0000);
			//buf[tmp * width_in_bytes + j * 3 + 0] = (data[i][j]) & 0xff;
			//buf[tmp * width_in_bytes + j * 3 + 1] = (data[i][j] >> 8) & 0xff;
			//buf[tmp * width_in_bytes + j * 3 + 2] = (data[i][j] >> 16) & 0xff;
		}
	}
}

void	write_file(unsigned char *header, unsigned char *buf,
					unsigned int size)
{
	int fd;

	fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	write(fd, header, 54);
	write(fd, buf, size);
	close(fd);
}

int		save_bmp(t_window win)
{
	unsigned char	header[54];
	unsigned char	*buf;
	unsigned int	wid_bytes;
	unsigned int	imgsize;

	wid_bytes = ((win.wid * 24 + 31) / 32) * 4;
	imgsize = wid_bytes * win.hei;
	set_header(header, win, imgsize);
	if (!(buf = malloc(imgsize)))
		return (0);
	set_pixels(buf, win, wid_bytes);
	write_file(header, buf, imgsize);
	free(buf);
	return (1);
}