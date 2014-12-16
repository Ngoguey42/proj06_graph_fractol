/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandelbrot_async.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 10:29:14 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/16 11:55:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int			julia_zero_escape_val(F_COO c, int max_loop)
{
	F_COO	zero;
	F_COO	tmp;
	int		i;

	ft_bzero(&zero, sizeof(F_COO));
	i = 0;
	while (i < max_loop)
	{
		i++;
		tmp = zero;
		zero.y = 2 * tmp.x * tmp.y + c.y;
		zero.x = tmp.x * tmp.x - tmp.y * tmp.y + c.x;
		if (STOPCOND(zero.x) || STOPCOND(zero.y))
			break ;
	}
	return (i);
}

int			fra_draw_line(t_fra fra, F_COO pix, int sta, int end)
{
	int		j;
	int		pair[2];

	pair[0] = julia_zero_escape_val(pix, fra.max_loop);
	PUTSDST(pair[0], sta);
	pair[1] = julia_zero_escape_val(
		ACOOTOL(pix.x + fra.pxin.x * 2, pix.y, 0), fra.max_loop);
	PUTSDST(pair[1], sta + 2);
	pix.x += fra.pxin.x;
	sta++;
	while (sta < end)
	{
		if (pair[0] == pair[1])
			PUTSDST(pair[0], sta);
		else
		{
			j = julia_zero_escape_val(pix, fra.max_loop);
			PUTSDST(j, sta);
		}
		pair[0] = pair[1];
		pair[1] = julia_zero_escape_val(
			ACOOTOL(pix.x + fra.pxin.x * 3, pix.y, 0), fra.max_loop);
		PUTSDST(pair[1], sta + 3);
		sta += 2;
		pix.x += fra.pxin.x * 2;
	}
	return (0);
}

void		fra_draw_mandelbrot2(t_fra fra)
{
	int			i;
	F_COO		pix;

	pix = fra.coo;
	i = -1 + WIN_Y / NUMTHREAD * (fra.part - 1);
	pix.y += fra.pxin.y * (F_T)(i + 1);
	while (i++ < WIN_Y / NUMTHREAD * fra.part)
	{
		fra_draw_line(fra, pix, i * WIN_X, (i + 1) * WIN_X);
		pix.y += fra.pxin.y;
	}
}

void		*threadsplit2(t_fra *fra)
{
	fra_draw_mandelbrot2(*fra);
	return (NULL);
}

void		*threadsplit(void *fra)
{
	return ((void*)threadsplit2((t_fra*)fra));
}

int			fra_draw_mandelbrot(t_fra fra)
{
	pthread_t	tid[NUMTHREAD];
	t_fra		frat[NUMTHREAD];
	int			precisionloss;
	int			i;

/* 	qprintf("salut"); */
	fra.max_loop = NLOOP;
	precisionloss = (F_NEXT(ABS(fra.coo.x), 1.0) >
					ABS(fra.coo.x) + ABS(fra.pxin.x));
	fra.precisionloss = precisionloss;
	i = 0;
	while (i < NUMTHREAD)
	{
		frat[i] = fra;
		frat[i].part = i + 1;
		pthread_create(&tid[i], NULL, threadsplit, &frat[i]);
		i++;
	}
	i = 0;
	while (i < NUMTHREAD)
		pthread_join(tid[i++], NULL);
	return (0);
}
