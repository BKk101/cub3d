#include "./cub3d.h"

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

void	set_pixels(unsigned char *buf, t_window win, unsigned int wid_bytes)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	tmp = win.hei;
	while (++i < win.hei)
	{
		j = -1;
		--tmp;
		while (++j < win.wid)
		{
			buf[tmp * wid_bytes + j * 3 + 0] = (win.scene[i][j]) & 0xff;
			buf[tmp * wid_bytes + j * 3 + 1] = (win.scene[i][j] >> 8) & 0xff;
			buf[tmp * wid_bytes + j * 3 + 2] = (win.scene[i][j] >> 16) & 0xff;
		}
	}
}

void	make_bmp(unsigned char *header, unsigned char *buf,
					unsigned int size)
{
	int fd;

	fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	write(fd, header, 54);
	write(fd, buf, size);
	close(fd);
}

void	save_bmp(t_window win)
{
	unsigned char	header[54];
	unsigned char	*buf;
	unsigned int	wid_bytes;
	unsigned int	imgsize;

	wid_bytes = win.wid * 3;
	imgsize = wid_bytes * win.hei;
	set_header(header, win, imgsize);
	buf = malloc(imgsize);
	set_pixels(buf, win, wid_bytes);
	make_bmp(header, buf, imgsize);
	free(buf);
}
