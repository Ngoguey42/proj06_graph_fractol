/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 12:04:06 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/25 10:41:22 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

#define PIXCOLOR(A) fra->themes[fra->theme]((A), fra->max_loop)
#define PUTSDST(A, B) fra_puts_dst(&fra->s, (B) * 4, PIXCOLOR(A))

int			fra_draw_row1(const t_fra *fra, F_COO pix, int sta, int end)
{
	while (sta < end)
	{
		fra_puts_dst(&fra->s, sta * 4, PIXCOLOR(fra->fra_func(pix, fra)));
		sta++;
		pix.x += fra->pxin.x;
	}
	return (0);
}

int			fra_draw_row2(const t_fra *fra, F_COO pix, int sta, int end)
{
	int		pair[2];

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
			PUTSDST(fra->fra_func(pix, fra), sta);
		pair[0] = pair[1];
		pair[1] = fra->fra_func(
			ACOOTOL(pix.x + fra->pxin.x * 3, pix.y, 0), fra);
		PUTSDST(pair[1], sta + 3);
		sta += 2;
		pix.x += fra->pxin.x * 2;
	}
	return (0);
}

int			fra_draw_row1_preci(const t_fra *fra, F_COO pix, int sta, int end)
{
	int		i;

	i = 0;
	while (sta < end)
	{
		pix.x = fra->coo.x + fra->pxin.x * (F_T)i++;
		fra_puts_dst(&fra->s, sta * 4, PIXCOLOR(fra->fra_func(pix, fra)));
		sta++;
	}
	return (0);
}
