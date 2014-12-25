/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screenpart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 12:12:44 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/25 10:39:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

F_T		fra_get_n_nextval(F_T val, int n)
{
	while (n--)
		val = F_NEXT(val, M_INFINITY);
	return (val);
}

int		fra_draw_scpart(const t_fra *fra, int part)
{
	int		i;
	F_COO	pix;

	pix = fra->coo;
	i = -1 + WIN_Y / NUMTHREAD * (part - 1);
	pix.y += fra->pxin.y * (F_T)(i + 1);
	while (i++ < WIN_Y / NUMTHREAD * part)
	{
		fra_draw_row2(fra, pix, i * WIN_X, (i + 1) * WIN_X);
		pix.y += fra->pxin.y;
	}
	return (0);
}

int		fra_draw_scpart_precisionloss(const t_fra *fra, int part)
{
	int		i;
	F_COO	pix;

	i = -1 + WIN_Y / NUMTHREAD * (part - 1);
	while (i++ < WIN_Y / NUMTHREAD * part)
	{
		pix.y = fra->coo.y + fra->pxin.y * (F_T)i;
		fra_draw_row1_preci(fra, pix, i * WIN_X, (i + 1) * WIN_X);
	}
	return (0);
}
