/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sierpinski.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 09:28:28 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 09:41:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdlib.h>

int			sierpinski_state(F_COO pix, t_fra fra)
{
	int		i;
	F_T		tmp;

	i = 0;
	while (i++ <= fra.max_loop)
	{
		if (pix.x < 0 || pix.x > 3)
			return (fra.max_loop);
		tmp = F_MOD(pix.x / fra.sierp_deltas[i], 3);
		if (tmp > 1 || tmp < 2)
			break ;
	}
	return (i);
}

static int		fra_draw_line(t_fra fra, F_COO pix, int sta, int end)
{
	int		j;

/* 	int		pair[2]; */

	// pair[0] = julia_zero_escape_val(pix, fra.max_loop);
	// fra_puts_dst(fra, sta * 4, (pair[0] < fra.max_loop) ?
				// VCOTOI((pair[0] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
	// pair[1] = julia_zero_escape_val(ACOOTOL(pix.x + fra.pxin.x * 2, pix.y, 0), fra.max_loop);
	// fra_puts_dst(fra, (sta + 2) * 4, (pair[1] < fra.max_loop) ?
				// VCOTOI((pair[1] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
	// pix.x += fra.pxin.x;
	// sta++;
	// while (sta < end)
	// {
		// if (pair[0] == pair[1])
			// fra_puts_dst(fra, sta * 4, (pair[0] < fra.max_loop) ?
						// VCOTOI((pair[0] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		// else
		// {
			// j = julia_zero_escape_val(pix, fra.max_loop);
			// fra_puts_dst(fra, sta * 4, (j < fra.max_loop) ?
						// VCOTOI((j * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		// }
		// pair[0] = pair[1];
		// pair[1] = julia_zero_escape_val(ACOOTOL(pix.x + fra.pxin.x * 3, pix.y, 0), fra.max_loop);
		// fra_puts_dst(fra, (sta + 3) * 4, (pair[1] < fra.max_loop) ?
					// VCOTOI((pair[1] * 7) % 256, 0, 0, 0) : VCOTOI(0, 0, 0, 0));
		// sta += 2;
		// pix.x += fra.pxin.x * 2;
	// }
	// qprintf("salut  %d %d\n", sta, end);
		
 	while (sta < end) 
 	{			 
 		if ((j = sierpinski_state(pix, fra)) < fra.max_loop) 
 			fra_puts_dst(fra, sta * 4, VCOTOI((j * 7) % 256, 0, 0, 0)); 
 		else 
 			fra_puts_dst(fra, sta * 4, VCOTOI(0, 0, 0, 0)); 
 		sta++;
 		pix.x += fra.pxin.x; 
 	} 
	return (1);
}

int			fra_draw_sierpinski(t_fra fra)
{
	int			i;
/* 	int			j; */
	F_COO		pix;
/* 	F_T			test; */
	// qprintf("salut  00\n");
	
	qprintf("drawing");
    fra.max_loop = 4;
    fra.precisionloss = (F_NEXT(ABS(fra.coo.x), 1.0) >
					 ABS(fra.coo.x) + ABS(fra.pxin.x));
	pix = fra.coo;
	i = -1;
	// qprintf("salut  00\n");
	pix.y += fra.pxin.y;
	// qprintf("salut  004\n");
	while (i++ < WIN_Y)
	{
		fra_draw_line(fra, pix, i * WIN_X, (i + 1) * WIN_X);
		pix.y += fra.pxin.y;
	}
	// qprintf("salut  005\n");
	return (0);
}
