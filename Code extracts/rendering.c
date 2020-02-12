/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:45:37 by gbianco           #+#    #+#             */
/*   Updated: 2019/03/08 03:26:49 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	vertical_line(t_container *c, int *x, int *y)
{
	t_point p1;
	t_point p2;

	p1.x = *x;
	p1.y = *y;
	p1.z = c->file.z[c->file.columns * *y + *x];
	p1.cl = c->file.cl[c->file.columns * *y + *x];
	p2.x = *x;
	p2.y = *y + 1;
	p2.z = c->file.z[c->file.columns * (*y + 1) + *x];
	p2.cl = c->file.cl[c->file.columns * (*y + 1) + *x];
	transform_line(c, &p1, &p2);
	put_line(c, &p1, &p2);
}

void	horizontal_line(t_container *c, int *x, int *y)
{
	t_point p1;
	t_point p2;

	p1.x = *x;
	p1.y = *y;
	p1.z = c->file.z[c->file.columns * *y + *x];
	p1.cl = c->file.cl[c->file.columns * *y + *x];
	p2.x = *x + 1;
	p2.y = *y;
	p2.z = c->file.z[c->file.columns * *y + (*x + 1)];
	p2.cl = c->file.cl[c->file.columns * *y + (*x + 1)];
	transform_line(c, &p1, &p2);
	put_line(c, &p1, &p2);
}

void	put_instruction(t_container *c)
{
	mlx_string_put(c->view.mlx, c->view.win, 3, 3, c->file.color,
			"Change View (1)(2)(3)(4) | Active/Deactivate Disco mode (p)");
	mlx_string_put(c->view.mlx, c->view.win, 3, 23, c->file.color,
			"Select mode: Move(m) AxeX(x) AxeY(y) AxeZ(z) Depth(d)");
	mlx_string_put(c->view.mlx, c->view.win, 3, 43, c->file.color,
			"Modify variable of mode: (arrows) | Zoom (+)(-)");
}

void	generate_map(t_container *c)
{
	int	x;
	int	y;

	y = 0;
	while (y < c->file.lines)
	{
		x = 0;
		while (x < c->file.columns)
		{
			if (y < c->file.lines - 1)
				vertical_line(c, &x, &y);
			if (x < c->file.columns - 1)
				horizontal_line(c, &x, &y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(c->view.mlx, c->view.win, c->view.img, 0, 0);
	put_instruction(c);
	mlx_destroy_image(c->view.mlx, c->view.img);
}

void	regenerate_map(t_container *c)
{
	if (!(c->view.img = mlx_new_image(c->view.mlx, c->view.width,
					c->view.height)))
		error(c, 0);
	if (!(c->view.str = mlx_get_data_addr(c->view.img, &(c->view.bpp),
					&(c->view.sz_line), &(c->view.endian))))
		error(c, 0);
	generate_map(c);
}
