/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 07:57:12 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/25 11:10:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

/*
** 'fra_eval_screen_coords' Convert the integer mouse coords on-screen, floating
**							  coords in the 2d plane. Calls once before redraw.
**							  Julia only.
** 'fra_apply_zoom'			Applies the zoom, both ways.
** 'fra_move'				Is called by ft_clock, applies movements.
**								See libft/includes/ft_clock.h
*/

int			fra_eval_screen_coords(t_fra *fra, int x, int y)
{
	fra->m_coo = ACOOTOL(fra->coo.x + fra->pxin.x * (F_T)x,
						fra->coo.y + fra->pxin.y * (F_T)y, 0);
	return (0);
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
	fra->coo.x += (-fra->scdt.x + prev.x) *
		((F_T)fra->m_cooscr.x / (F_T)WIN_X);
	fra->coo.y += (-fra->scdt.y + prev.y) *
		((F_T)fra->m_cooscr.y / (F_T)WIN_Y);
	fra->redraw = 1;
	return (0);
}

int			fra_move(t_fra *fra, clock_t el)
{
	if (!(fra->ev[4] == fra->ev[5]))
	{
		fra->coo.x += (F_T)el / SPEEDFACT * (1 - fra->ev[4] * 2) / fra->zoom;
		fra->redraw = 1;
	}
	if (!(fra->ev[0] == fra->ev[1]))
	{
		fra->coo.y += (F_T)el / SPEEDFACT * (1 - fra->ev[1] * 2) / fra->zoom;
		fra->redraw = 1;
	}
	return (0);
}

int			fra_move_void(void *fra, clock_t el)
{
	return (fra_move((t_fra*)fra, el));
}
