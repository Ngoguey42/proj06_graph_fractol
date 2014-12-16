/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 07:57:12 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/16 12:19:26 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int			fra_eval_screen_coords(t_fra *fra, int x, int y)
{
	fra->m_coo = ACOOTOL(fra->coo.x + fra->pxin.x * (F_T)x,
						fra->coo.y + fra->pxin.y * (F_T)y, 0);
	fra->redraw = 1;
}

int			fra_apply_zoom(t_fra *fra, F_T delta)
{
	F_COO	prev;

	fra->zoom *= delta;
	prev = fra->scdt;
	fra->scdt.y = -1. / fra->zoom;
	fra->scdt.x = +1. / fra->zoom;
	fra->pxin.x = fra->scdt.x / WIN_X;
	fra->pxin.y = fra->scdt.y / WIN_Y;
/* 	qprintf("mousex:%d   mousexx%%%.2Lf\n", fra->m_cooscr.x, ((F_T)fra->m_cooscr.x / (F_T)WIN_X)); */
	fra->coo.x += (- fra->scdt.x + prev.x) * ((F_T)fra->m_cooscr.x / (F_T)WIN_X);
	fra->coo.y += (- fra->scdt.y + prev.y) * ((F_T)fra->m_cooscr.y / (F_T)WIN_Y);
	fra->redraw = 1;
/* 	fra_eval_screen_coords(fra, fra->m_cooscr.x, fra->m_cooscr.y); */
	return (0);
}

int			fra_move(t_fra *fra)
{
	int		t;

	t = 0;
	if (!(fra->ev[4] == fra->ev[5]))
	{
		fra->coo.x += XYSPEEDBASE * (1 - fra->ev[4] * 2) / fra->zoom;
		t = 1;
	}
	if (!(fra->ev[0] == fra->ev[1]))
	{
		fra->coo.y += XYSPEEDBASE * (1 - fra->ev[1] * 2) / fra->zoom;
		t = 1;
	}
/* 	if (!(fra->ev[2] == fra->ev[3])) */
/* 	{ */
/* 		qprintf("salut"); */
/* 		fra->coo.y += XYSPEEDBASE * (1 - fra->ev[1] * 2) / fra->zoom; */
/* 		fra_apply_zoom(fra, ZOOMSPEEDBASE * (1 - fra->ev[11] * 2)); */
/* 		t = 1; */
/* 	} */
	if (t)
	{
		fra_eval_screen_coords(fra, fra->m_cooscr.x, fra->m_cooscr.y);
		fra->redraw = 1;
	}
	return (0);
}

int			fra_move_void(void *fra)
{
	return (fra_move((t_fra*)fra));
}
