/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 12:42:05 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/25 10:24:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void	build_sierp_deltas_tab(t_fra *fra)
{
	int		 i;

	i = -1;
	while (++i < MAX_SIERP_LOOPS)
		fra->sierp_deltas[i] = (F_T)(3.L / powl(3.L, (long double)i));
}

void		fra_init_pertype(t_fra *fra, int type)
{
	fra->type = type;
	if (type == 2)
	{
		fra->fra_func = fra_mandelbrot;
		fra->theme = 0;
	}
	else if (type == 3)
	{
		build_sierp_deltas_tab(fra);
		fra->fra_func = fra_sierpinski;
		fra->theme = 1;
	}
	else
	{
		fra->fra_func = fra_julia;
		fra->theme = 2;
	}
}

void		fra_init_env(t_fra *fra, int type)
{
	fra->loop_coef = 1.;
	fra_init_pertype(fra, type);
	fra->mvmt_clockev.f = &fra_move_void;
	fra->mvmt_clockev.data = fra;
	fra->mvmt_clockev.dt = DELTA_MVMT_CALLS;
	fra->mvmt_clockev.type = 0x13;
	fra_set_defpos(fra);
	fra->themes[0] = &fra_theme_0;
	fra->themes[1] = &fra_theme_1;
	fra->themes[2] = &fra_theme_2;
}
