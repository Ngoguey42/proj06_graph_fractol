/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:35:39 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 10:18:30 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fractol.h>

int	fra_show_hud(t_fra fra)
{
	char	buffer[80];
	t_co	co;
	t_cooi	cooi;

	co = VCOTOI(255, 255, 255, 0);
	cooi = ACOOTOI(WIN_X - 120, WIN_Y - 85, 0);
	ft_sprintf(buffer, "%13s %s", "Movements:", "WASD");
	fra_put_string(fra, ICOOADDY(cooi, 0), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Zoom:", "Scroll");
	fra_put_string(fra, ICOOADDY(cooi, 15), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Positions:", "OP");
	fra_put_string(fra, ICOOADDY(cooi, 30), co, buffer);
	ft_sprintf(buffer, "%13s %s", "This frame:", "I");
	fra_put_string(fra, ICOOADDY(cooi, 45), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Num-loop coef:", "-+");
	fra_put_string(fra, ICOOADDY(cooi, 60), co, buffer);
	ft_sprintf(buffer, "        (%d loops)", NLOOP);
	fra_put_string(fra, ICOOADDY(cooi, 75), co, buffer);
	return (0);
}

int	fra_set_defpos1(t_fra *fra)
{
	fra->coo.x = STARTCAMX1;
	fra->coo.y = STARTCAMY1;
	fra->zoom = STARTZOOM1;
	fra->scdt.y = -1. / STARTZOOM1;
	fra->scdt.x = +1. / STARTZOOM1;
	fra_apply_zoom(fra, 1);
	return (0);
}

int	fra_set_defpos2(t_fra *fra)
{
	fra->coo.x = STARTCAMX2;
	fra->coo.y = STARTCAMY2;
	fra->zoom = STARTZOOM2;
	fra->scdt.y = -1. / STARTZOOM2;
	fra->scdt.x = +1. / STARTZOOM2;
	fra_apply_zoom(fra, 1);
	return (0);
}

void	build_sierp_deltas_tab(t_fra *fra)
{
	int			i;

	i = -1;
	while (++i < MAX_SIERP_LOOPS)
		fra->sierp_deltas[i] = (F_T)(3.L / powl(3.L, (long double)i));
}

int	main(int ac, char *av[])
{
	t_fra	reffra;
	F_T		sierp_deltas[MAX_SIERP_LOOPS];

	ft_bzero(&reffra, sizeof(t_fra));
	reffra.type = 3;
	reffra.loop_coef = 1.;
	reffra.sierp_deltas = (F_T*)&sierp_deltas;
	if (reffra.type == 3)
		build_sierp_deltas_tab(&reffra);
	reffra.mvmt_clockev.f = &fra_move_void;
	reffra.mvmt_clockev.data = &reffra;
	reffra.mvmt_clockev.dt = DELTA_MVMT_CALLS;
	reffra.mvmt_clockev.type = 0x13;
	fra_set_defpos2(&reffra);
/* 	fra_read_input(ac, av, reffra, frat); */
	if (fra_init_window(&reffra))
		return (1);
	fra_pause(&reffra);
	(void)ac;
	(void)av;
	return (0);
}
