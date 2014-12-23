/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sierpinski_async.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 10:00:01 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 10:58:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int prev = 48515;

int		 sierpinski_state(F_COO pix, int max_loop, F_T *deltas)
{
	int	i;
	F_T	tmp;

	i = 0;
/* 	qprintf("1"); */
	if (pix.x < 0 || pix.x > 3 || pix.y < 0 || pix.y > 3)
		return (-1);
	while (i++ <= max_loop)
	{
		tmp = F_MOD(pix.x / deltas[i], 3);
		if (tmp > 1 && tmp < 2)
		{
			tmp = F_MOD(pix.y / deltas[i], 3);
			if (tmp > 1 && tmp < 2)
				break ;
		}
	}


	return (i);
	while (i++ <= max_loop)
	{
		if (pix.x < 0 || pix.x > 3)
			return (-1);
		tmp = F_MOD(pix.x / deltas[i], 3);
		if (tmp > 1 && tmp < 2)
			break ;
	}
/* 	if (prev != i) */
/* 	{ */
/* 		qprintf("%d %lle\n", i, tmp); */
/* 	} */
/* 	prev = i; */

	return (i);
}

static int			fra_draw_line(t_fra fra, F_COO pix, int sta, int end)
{
	int		j;
/* 	int		pair[2]; */

/* 	pair[0] = sierpinski_state(pix, fra); */
/* 	PUTSDST(pair[0], sta); */
/* 	pair[1] = sierpinski_state( */
/* 		ACOOTOL(pix.x + fra.pxin.x * 2, pix.y, 0), fra); */
/* 	PUTSDST(pair[1], sta + 2); */
/* 	pix.x += fra.pxin.x; */
/* 	sta++; */
/* 	while (sta < end) */
/* 	{ */
/* 		if (pair[0] == pair[1]) */
/* 			PUTSDST(pair[0], sta); */
/* 		else */
/* 		{ */
/* 			j = sierpinski_state(pix, fra); */
/* 			PUTSDST(j, sta); */
/* 		} */
/* 		pair[0] = pair[1]; */
/* 		pair[1] = sierpinski_state( */
/* 			ACOOTOL(pix.x + fra.pxin.x * 3, pix.y, 0), fra); */
/* 		PUTSDST(pair[1], sta + 3); */
/* 		sta += 2; */
/* 		pix.x += fra.pxin.x * 2; */
/* 	} */
    while (sta < end)
    {
        if ((j = sierpinski_state(pix, fra.max_loop, fra.sierp_deltas)) < 0)
			fra_puts_dst(fra, sta * 4, VCOTOI(255, 255, 255, 0));
        else if (j < fra.max_loop)
            fra_puts_dst(fra, sta * 4, VCOTOI(
							 55 + (j * 18) % 200,
							 0,
							 55 + (-j * 22) % 200,
							 0));
        else
            fra_puts_dst(fra, sta * 4, VCOTOI(0, 0, 0, 0));
        sta++;
        pix.x += fra.pxin.x;
    }

	return (0);
}

static void		fra_draw_mandelbrot2(t_fra fra)
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

static void		*threadsplit2(t_fra *fra)
{
	fra_draw_mandelbrot2(*fra);
	return (NULL);
}

static void		*threadsplit(void *fra)
{
	return ((void*)threadsplit2((t_fra*)fra));
}

int			fra_draw_sierpinski(t_fra fra)
{
	pthread_t	tid[NUMTHREAD];
	t_fra		frat[NUMTHREAD];
	int			precisionloss;
	int			i;


/* 	qprintf("salut"); */
	fra.max_loop = NLOOP3;

/* 	qprintf("zoom: %.2Lf  %d\n", fra.zoom, fra.max_loop); */

	qprintf("coef * floor(log2(zoom) + 7)\n");
	qprintf("%.1LF * floor(log2(%5.2Lf) + 7)\n", fra.loop_coef, fra.zoom);
	qprintf("%.1LF * floor(%5.2Lf + 7)\n", fra.loop_coef, F_LG(fra.zoom));
	qprintf("%d\n\n", fra.max_loop);

/* 	precisionloss = (F_NEXT(ABS(fra.coo.x), 1.0) > */
/* 					ABS(fra.coo.x) + ABS(fra.pxin.x)); */
/* 	fra.precisionloss = precisionloss; */
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
