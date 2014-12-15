/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 07:44:42 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/15 16:19:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>

int	fra_init_window(t_fra *fra)
{
	if (!(SERVP = mlx_init()))
	{
		ft_dprintf(2, "Could not establish connection to X-Window server.\n");
		return (1);
	}
	ft_dprintf(2, "Established connection to X-Window server. %p\n", SERVP);
    if (!(fra->win1 = mlx_new_window(SERVP, WIN_X, WIN_Y, "fra")))
    {
        ft_dprintf(2, "Could not create new window.\n");
        return (1);
    }
    ft_dprintf(2, "New window created. %p\n", WIN1P);
    mlx_expose_hook(WIN1P, &fra_expose_hook, (void*)fra);
    mlx_hook(WIN1P, 2, 1, &fra_keydo_hook, (void*)fra);
    mlx_hook(WIN1P, 3, 2, &fra_keyup_hook, (void*)fra);
	qprintf("sent %p\n", fra);
    mlx_hook(WIN1P, 4, 0x04, &fra_butdo_hook, (void*)fra);
/*     mlx_hook(WIN1P, 5, 0x08, &fra_butup_hook, (void*)fra); */
/*     mlx_hook(WIN1P, KeyPress, KeyPressMask, &fra_keydo_hook, fra); */
/*     mlx_hook(WIN1P, KeyRelease, KeyReleaseMask, &fra_keyup_hook, fra); */
/*     mlx_hook(WIN1P, ButtonPress, ButtonPressMask, &fra_butdo_hook, fra); */
/*     mlx_hook(WIN1P, ButtonRelease, ButtonReleaseMask, &fra_butup_hook, fra); */

/* 	mlx_mouse_hook(WIN1P, &fra_keydo_hook, fra); */
    mlx_loop_hook(SERVP, &fra_loop_hook, fra);
	fra->s.img = mlx_new_image(SERVP, WIN_X, WIN_Y);
	fra->s.dat = mlx_get_data_addr(fra->s.img, &fra->s.bpp,
							&fra->s.lsz, &fra->s.end);
/* 	fra->s.totby = WIN_X * WIN_Y * (fra->s.bpp / 8); */
	ft_dprintf(2, "New Img: x(%d) y(%d) ptr(%p) dat(%p):\n",
			WIN_X, WIN_Y, fra->s.img, fra->s.dat);
	ft_dprintf(2, "\t bpp(%d) linesize(%d) endian(%d)\n",
			fra->s.bpp, fra->s.lsz, fra->s.end);
	return (0);
}

int	fra_init_surface(t_fra fra)
{
	(void)fra;
/* 	mlx_clear_window(SERV, WIN1); */
	return (0);
}

int fra_set_surface(t_fra fra)
{
/* 	if (fra.type == 1) */
/* 		fra_draw_julia(fra); */
/* 	else if (fra.type == 2) */
		fra_draw_mandelbrot(fra);
	mlx_put_image_to_window(SERV, WIN1, fra.s.img, 0, 0);
	return (0);
}

int	fra_push_surface(t_fra fra)
{
	(void)fra;
	//mdx_clean_surface
	return (0);
}

int	fra_quit(t_fra fra)
{
	mlx_destroy_window(SERV, WIN1);
	(void)fra;
	exit(EXIT_SUCCESS);
}
