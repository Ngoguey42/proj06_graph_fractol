/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 16:08:34 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/15 16:15:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define NLOOP (int)(70. * ((fra.zoom > 10) ? F_LG(fra.zoom) / F_LG(10): 1.))
#define STOPCOND(ARG) (ARG > 100.)

static int			julia_escapeval(F_COO pix, int max_loop, F_COO c)
{
	F_COO	pix;
	F_COO	tmp;
	int		i;

	ft_bzero(&pix, sizeof(F_COO));
	i = 0;
	while (i < max_loop)
	{
		i++;
		tmp = pix;
		pix.y = 2 * tmp.x * tmp.y + c.y;
		pix.x = tmp.x * tmp.x - tmp.y * tmp.y + c.x;
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}

static int		fra_draw_line(t_fra fra, F_COO pix, int sta, int end)
{
	int		j;

	int		pair[2];

	pair[0] = julia_escapeval(pix, fra.max_loop, fra.m_coo);
	fra_puts_dst(fra, sta * 4, (pair[0] < fra.max_loop, fra.m_coo) ?
				VCOTOI((pair[0] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
	pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 2, pix.y, 0),
							  fra.max_loop, fra.m_coo);
	fra_puts_dst(fra, (sta + 2) * 4, (pair[1] < fra.max_loop, fra.m_coo) ?
				VCOTOI((pair[1] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
	pix.x += fra.pxin.x;
	sta++;
	while (sta < end)
	{
		if (pair[0] == pair[1])
			fra_puts_dst(fra, sta * 4, (pair[0] < fra.max_loop, fra.m_coo) ?
						VCOTOI((pair[0] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		else
		{
			j = julia_escapeval(pix, fra.max_loop, fra.m_coo);
			fra_puts_dst(fra, sta * 4, (j < fra.max_loop, fra.m_coo) ?
						VCOTOI((j * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		}
		pair[0] = pair[1];
		pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 3, pix.y, 0),
								  fra.max_loop, fra.m_coo);
		fra_puts_dst(fra, (sta + 3) * 4, (pair[1] < fra.max_loop, fra.m_coo) ?
					VCOTOI((pair[1] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		sta += 2;
		pix.x += fra.pxin.x * 2;
	}
		
/* 	while (sta < end) */
/* 	{			 */
/* 		if ((j = julia_escapeval(pix, fra.max_loop, fra.m_coo)) < fra.max_loop, fra.m_coo) */
/* 			fra_puts_dst(fra, sta * 4, VCOTOI((j * 7) % 256, 0, 0, 0)); */
/* 		else */
/* 			fra_puts_dst(fra, sta * 4, VCOTOI(0, 0, 0, 0)); */
/* 		sta++; */
/* 		pix.x += fra.pxin.x; */
/* 	} */
}

static void		fra_draw_julia2(t_fra fra)
{
	int			i;
	int			j;
	F_COO		pix;
	F_T			test;

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
	fra_draw_julia2(*fra);
	return (NULL);
}

static void		*threadsplit(void *fra)
{
	return ((void*)threadsplit2((t_fra*)fra));
}

int			fra_draw_julia(t_fra fra)
{
	pthread_t	tid[NUMTHREAD];
	t_fra		frat[NUMTHREAD];
	int			precisionloss;
	int			i;

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
