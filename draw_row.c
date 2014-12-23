/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 12:04:06 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 12:37:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

#define _PD1(A) (A < fra->max_loop)
#define _PD2(A) VCOTOI((A * 7) % 256, 0, 0, 0)
#define _PD3 VCOTOI(0, 0, 0, 255)
#define PUTSDST(A, B) fra_puts_dst(&fra->s, (B) * 4, _PD1(A) ? _PD2(A) : _PD3)

int			fra_draw_row1(const t_fra *fra, F_COO pix, int sta, int end)
{
	int		j;

	while (sta < end)
	{
		if ((j = fra->fra_func(pix, fra)) < 0)
			fra_puts_dst(&fra->s, sta * 4, VCOTOI(255, 255, 255, 0));
		else if (j < fra->max_loop)
			fra_puts_dst(&fra->s, sta * 4, VCOTOI(
							 55 + (j * 18) % 200,
							 0,
							 55 + (-j * 22) % 200,
							 0));
		else
			fra_puts_dst(&fra->s, sta * 4, VCOTOI(0, 0, 0, 0));
		sta++;
		pix.x += fra->pxin.x;
	}
	return (0);
}

int			fra_draw_row2(const t_fra *fra, F_COO pix, int sta, int end)
{
	int	 j;
	int	 pair[2];
	
	pair[0] = fra->fra_func(pix, fra);
	PUTSDST(pair[0], sta);
	pair[1] = fra->fra_func(
		ACOOTOL(pix.x + fra->pxin.x * 2, pix.y, 0), fra);
	PUTSDST(pair[1], sta + 2);
	pix.x += fra->pxin.x;
	sta++;
	while (sta < end)
	{
		if (pair[0] == pair[1])
			PUTSDST(pair[0], sta);
		else
		{
			j = fra->fra_func(pix, fra);
			PUTSDST(j, sta);
		}
		pair[0] = pair[1];
		pair[1] = fra->fra_func(
			ACOOTOL(pix.x + fra->pxin.x * 3, pix.y, 0), fra);
		PUTSDST(pair[1], sta + 3);
		sta += 2;
		pix.x += fra->pxin.x * 2;
	}
	return (0);
}
