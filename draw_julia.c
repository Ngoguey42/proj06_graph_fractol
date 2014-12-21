/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 07:55:05 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/16 08:20:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdlib.h>

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
		pix = ft_cmult(pix, pix);
		pix.x += c.x;
		pix.y += c.y;
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}


	// pair[0] = julia_escapeval(pix, fra.max_loop, fra.m_coo);
	// pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 2, pix.y, 0),
							  // fra.max_loop, fra.m_coo);
			// j = julia_escapeval(pix, fra.max_loop, fra.m_coo);
		// pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 3, pix.y, 0),
								  // fra.max_loop, fra.m_coo);

								  
								  
static int	fra_draw_line(t_fra fra, F_COO pix, int sta, int end)
{
	int		j;

	int		pair[2];

	pair[0] = julia_escapeval(pix, fra.max_loop, fra.m_coo);
	fra_puts_dst(fra, sta * 4, (pair[0] < fra.max_loop) ?
				VCOTOI((pair[0] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
	pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 2, pix.y, 0), fra.max_loop, fra.m_coo);
	fra_puts_dst(fra, (sta + 2) * 4, (pair[1] < fra.max_loop) ?
				VCOTOI((pair[1] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
	pix.x += fra.pxin.x;
	sta++;
	while (sta < end)
	{
		if (pair[0] == pair[1])
			fra_puts_dst(fra, sta * 4, (pair[0] < fra.max_loop) ?
						VCOTOI((pair[0] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		else
		{
			j = julia_escapeval(pix, fra.max_loop, fra.m_coo);
			fra_puts_dst(fra, sta * 4, (j < fra.max_loop) ?
						VCOTOI((j * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		}
		pair[0] = pair[1];
		pair[1] = julia_escapeval(ACOOTOL(pix.x + fra.pxin.x * 3, pix.y, 0), fra.max_loop, fra.m_coo);
		fra_puts_dst(fra, (sta + 3) * 4, (pair[1] < fra.max_loop) ?
					VCOTOI((pair[1] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		sta += 2;
		pix.x += fra.pxin.x * 2;
	}
}

int			fra_draw_julia(t_fra fra)
{
	int			i;
	int			j;
	F_COO		pix;
	F_T			test;

    fra.max_loop = NLOOP;
    fra.precisionloss = (F_NEXT(ABS(fra.coo.x), 1.0) >
					 ABS(fra.coo.x) + ABS(fra.pxin.x));
	pix = fra.coo;
	i = -1;
	pix.y += fra.pxin.y;
	while (i++ < WIN_Y)
	{
		fra_draw_line(fra, pix, i * WIN_X, (i + 1) * WIN_X);
		pix.y += fra.pxin.y;
	}
	return (0);
}
