/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 12:42:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/30 09:05:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void	build_sierp_deltas_tab(t_fra *fra)
{
	int	i;

	i = -1;
	while (++i < MAX_SIERP_LOOPS)
		fra->sierp_deltas[i] = (F_T)(3.L / powl(3.L, (long double)i));
}

int			fra_set_defpos(t_fra *fra)
{
	if (fra->type == 3)
	{
		fra->coo.x = STARTCAMX3;
		fra->coo.y = STARTCAMY3;
		fra->zoom = STARTZOOM3;
		fra->scdt.y = -1. / STARTZOOM3;
		fra->scdt.x = +1. / STARTZOOM3;
	}
	else
	{
		fra->coo.x = STARTCAMX2;
		fra->coo.y = STARTCAMY2;
		fra->zoom = STARTZOOM2;
		fra->scdt.y = -1. / STARTZOOM2;
		fra->scdt.x = +1. / STARTZOOM2;
	}
	fra_apply_zoom(fra, 1);
	return (0);
}

static void	set_func(t_fra *fra, int type)
{
	if (type == 2)
		fra->fra_func = fra_mandelbrot;
	else if (type == 3)
		fra->fra_func = fra_sierpinski;
	else if (type == 4)
		fra->fra_func = fra_tardis;		
	else if (type == 5)
		fra->fra_func = fra_douady;
	else if (type == 6)
		fra->fra_func = fra_toad;
	else if (type == 7)
		fra->fra_func = fra_bretzel;
	else if (type == 8)
		fra->fra_func = fra_test;
	else
		fra->fra_func = fra_julia;
	return ;
}

void		fra_init_pertype(t_fra *fra, int type)
{
	fra->type = type;
	fra_set_defpos(fra);
	if (type == 3)
		build_sierp_deltas_tab(fra);
	if (type == 2 || type == 4 || type == 5 || type == 6 || type == 7)
		fra->theme = 0;
	else if (type == 3 || type == 8)
		fra->theme = 1;
	else
		fra->theme = 2;
	set_func(fra, type);
}

void		fra_init_env(t_fra *fra, int type)
{
	fra->loop_coef = 1.;
	fra_init_pertype(fra, type);
	fra->mvmt_clockev.f = &fra_move_void;
	fra->mvmt_clockev.data = fra;
	fra->mvmt_clockev.dt = DELTA_MVMT_CALLS;
	fra->mvmt_clockev.type = 0x13;
	fra->themes[0] = &fra_theme_0;
	fra->themes[1] = &fra_theme_1;
	fra->themes[2] = &fra_theme_2;
}
