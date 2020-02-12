/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 00:05:23 by gbianco           #+#    #+#             */
/*   Updated: 2019/03/07 03:03:14 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	color_pixel(t_container *c, t_point *p1, t_point *p2, t_point *p)
{
	int pixel;

	if (c->chan.sbuz && c->chan.sbuz < 10000000)
		c->chan.sbuz = c->chan.sbuz + 1;
	if (c->chan.sbuz == 10000000)
		c->chan.sbuz = 1;
	if (p->x < c->view.width && p->y < c->view.height && p->x > 0 && p->y > 0)
	{
		pixel = (4 * (c->view.width * p->y)) + (4 * p->x);
		p->cl = calculate_gradient(p, p1, p2);
		*((int *)(c->view.str + pixel)) = p->cl + c->chan.sbuz;
	}
}

void	bresenham_y(t_container *c, t_point *p1, t_point *p2, t_point *p)
{
	int dx;
	int dy;
	int xi;
	int err;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	err = 2 * dx - dy;
	while (p->y != p2->y + 1)
	{
		color_pixel(c, p1, p2, p);
		if (err > 0)
		{
			p->x += xi;
			err = err - 2 * dy;
		}
		err = err + 2 * dx;
		p->y += 1;
	}
}

void	bresenham_x(t_container *c, t_point *p1, t_point *p2, t_point *p)
{
	int dx;
	int dy;
	int yi;
	int err;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	err = 2 * dy - dx;
	while (p->x != p2->x + 1)
	{
		color_pixel(c, p1, p2, p);
		if (err > 0)
		{
			p->y += yi;
			err = err - 2 * dx;
		}
		err = err + 2 * dy;
		p->x += 1;
	}
}

void	put_line(t_container *c, t_point *p1, t_point *p2)
{
	int		dx;
	int		dy;
	t_point	p;

	dx = abs(p2->x - p1->x);
	dy = abs(p2->y - p1->y);
	if ((dy < dx && p1->x > p2->x) || (dy >= dx && p1->y > p2->y))
		p = *p2;
	else
		p = *p1;
	if (dy < dx)
	{
		if (p1->x > p2->x)
			bresenham_x(c, p2, p1, &p);
		else
			bresenham_x(c, p1, p2, &p);
	}
	else
	{
		if (p1->y > p2->y)
			bresenham_y(c, p2, p1, &p);
		else
			bresenham_y(c, p1, p2, &p);
	}
}
