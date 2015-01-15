/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 07:44:42 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/15 09:30:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdlib.h>

int	fra_init_window(t_fra *fra)
{
	if (!(SERVP = mlx_init()))
	{
		ft_putendl_fd("Could not establish connection to X-Window server.", 2);
		return (1);
	}
	if (!(fra->win1 = mlx_new_window(SERVP, WIN_X, WIN_Y, "fra")))
	{
		ft_putendl_fd("Could not create new window.", 2);
		return (1);
	}
	mlx_expose_hook(WIN1P, &fra_expose_hook, (void*)fra);
	mlx_hook(WIN1P, 2, 1, &fra_keydo_hook, (void*)fra);
	mlx_hook(WIN1P, 3, 2, &fra_keyup_hook, (void*)fra);
	mlx_hook(WIN1P, 4, 0x04, &fra_butdo_hook, (void*)fra);
	mlx_hook(WIN1P, 6, 0x40, &fra_motion_hook, (void*)fra);
	mlx_loop_hook(SERVP, &fra_loop_hook, fra);
	fra->s.img = mlx_new_image(SERVP, WIN_X, WIN_Y);
	fra->s.dat = mlx_get_data_addr(fra->s.img, &fra->s.bpp,
							&fra->s.lsz, &fra->s.end);
	return (0);
}

int	fra_init_surface(const t_fra *fra)
{
	(void)fra;
	return (0);
}

int fra_set_surface(t_fra *fra)
{
	fra->precisionloss = (
		fra_get_n_nextval(ABS(fra->coo.x), 16) >
		ABS(fra->coo.x) + ABS(fra->pxin.x));
	if (fra->type == 3)
	{
		fra->max_loop = NLOOP3;
		if (fra->max_loop > MAX_SIERP_LOOPS)
			return (1);
	}
	else if (fra->type == 1)
		fra->max_loop = NLOOP2;
	else
		fra->max_loop = NLOOP;
	fra_draw_screen((const t_fra*)fra);
	return (0);
}

int	fra_push_surface(const t_fra *fra)
{
	mlx_put_image_to_window(SERVP, WIN1P, fra->s.img, 0, 0);
	return (0);
}

int	fra_quit(t_fra fra)
{
	mlx_destroy_window(SERV, WIN1);
	exit(EXIT_SUCCESS);
}
