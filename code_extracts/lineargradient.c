/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineargradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 01:46:56 by gbianco           #+#    #+#             */
/*   Updated: 2019/03/04 17:36:23 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_intensity(int *srt, int *end, int *curr, double *intensity)
{
	double placement;
	double distance;

	placement = *curr - *srt;
	distance = *end - *srt;
	*intensity = (distance == 0) ? 1 : (placement / distance);
}

int		gradient(int start, int end, double intensity)
{
	return ((int)((1 - intensity) * start + intensity * end));
}

int		calculate_gradient(t_point *p, t_point *p1, t_point *p2)
{
	int		red;
	int		green;
	int		blue;
	double	intensity;

	if (p->cl == p2->cl)
		return (p->cl);
	if (abs(p2->x - p1->x) > abs(p2->y - p2->y))
		calculate_intensity(&p1->x, &p2->x, &p->x, &intensity);
	else
		calculate_intensity(&p1->y, &p2->y, &p->y, &intensity);
	red = gradient((p1->cl >> 16) & 0xFF, (p2->cl >> 16) & 0xFF, intensity);
	green = gradient((p1->cl >> 8) & 0xFF, (p2->cl >> 8) & 0xFF, intensity);
	blue = gradient(p1->cl & 0xFF, p2->cl & 0xFF, intensity);
	return ((red << 16) | (green << 8) | blue);
}
