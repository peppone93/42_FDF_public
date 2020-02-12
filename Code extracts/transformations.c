/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 01:22:47 by gbianco           #+#    #+#             */
/*   Updated: 2019/03/04 17:40:44 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	select_scale(t_container *c)
{
	if (c->file.points > 0 && c->file.points <= 250)
		c->chan.scale = 30;
	if (c->file.points > 250 && c->file.points <= 1000)
		c->chan.scale = 18;
	if (c->file.points > 1000 && c->file.points <= 4000)
		c->chan.scale = 10;
	if (c->file.points > 4000 && c->file.points <= 12000)
		c->chan.scale = 6;
	if (c->file.points > 12000 && c->file.points <= 100000)
		c->chan.scale = 4;
	if (c->file.points > 100000)
		c->chan.scale = 2.2;
}

void	transform_line(t_container *c, t_point *p1, t_point *p2)
{
	select_scale(c);
	c->chan.scale *= c->chan.zoom;
	p1->x *= c->chan.scale;
	p1->y *= c->chan.scale;
	p1->z *= c->chan.scale * 0.3 * c->chan.depth;
	p2->x *= c->chan.scale;
	p2->y *= c->chan.scale;
	p2->z *= c->chan.scale * 0.3 * c->chan.depth;
	p1->x -= ((c->file.columns - 1) * c->chan.scale) * 0.5;
	p1->y -= ((c->file.lines - 1) * c->chan.scale) * 0.5;
	p2->x -= ((c->file.columns - 1) * c->chan.scale) * 0.5;
	p2->y -= ((c->file.lines - 1) * c->chan.scale) * 0.5;
	x_axe_rotation(c, p1, p2);
	y_axe_rotation(c, p1, p2);
	z_axe_rotation(c, p1, p2);
	p1->x += (c->view.width * 0.5) + c->chan.modx;
	p1->y += (c->view.height * 0.5) + c->chan.mody;
	p2->x += (c->view.width * 0.5) + c->chan.modx;
	p2->y += (c->view.height * 0.5) + c->chan.mody;
}
