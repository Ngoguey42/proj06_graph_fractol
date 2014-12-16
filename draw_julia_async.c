/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 16:08:34 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/16 13:25:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

F_COO				ft_cmult(F_COO c1, F_COO c2)
{
	F_T	tmp;

	tmp = c1.x;
	c1.x = c1.x * c2.x - c1.y * c2.y;
	c1.y = tmp * c2.y + c1.y * c2.x;
	return (c1);
}


static int			julia_escapeval(F_COO pix, int max_loop, F_COO c)
{
	F_COO	tmp;
	int		i;

	i = 0;
	while (i < max_loop)
	{
		i++;
/* 		tmp = pix; */
/* 		pix.y = 2 * tmp.x * tmp.y + c.y; */
/* 		pix.x = tmp.x * tmp.x - tmp.y * tmp.y + c.x; */
/* 		pix = ft_cmult(ft_cmult(pix, pix), ft_cmult(ft_cmult(pix, pix), ft_cmult(pix, pix))); */
/* 		pix = ft_cmult(ft_cmult(pix, pix), pix); */
		pix = ft_cmult(pix, pix);
		pix.x += c.x;
		pix.y += c.y;
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
	PUTSDST(pair[0], sta);
	pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 2, pix.y, 0),
							  fra.max_loop, fra.m_coo);
	PUTSDST(pair[1], sta + 2);
	pix.x += fra.pxin.x;
	sta++;
	while (sta < end)
	{
		if (pair[0] == pair[1])
			PUTSDST(pair[0], sta);
		else
		{
			j = julia_escapeval(pix, fra.max_loop, fra.m_coo);
			PUTSDST(j, sta);
		}
		pair[0] = pair[1];
		pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 3, pix.y, 0),
								  fra.max_loop, fra.m_coo);
		PUTSDST(pair[1], sta + 3);
		sta += 2;
		pix.x += fra.pxin.x * 2;
	}
	return (0);
}

static void		fra_draw_julia2(t_fra fra)
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

	qprintf("%.5Lf %.5Lf\n", fra.m_coo.x, fra.m_coo.y);
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
