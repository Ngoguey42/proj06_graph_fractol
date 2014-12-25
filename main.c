/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:35:39 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/25 10:12:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fractol.h>

int	fra_show_hud(const t_fra *fra)
{
	char	buffer[80];
	t_co	co;
	t_cooi	cooi;

	co = VCOTOI(255, 255, 255, 0);
	cooi = ACOOTOI(WIN_X - 120, WIN_Y - 85, 0);
	ft_sprintf(buffer, "%13s %s", "Movements:", "WASD");
	fra_put_string(*fra, ICOOADDY(cooi, 0), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Zoom:", "Scroll");
	fra_put_string(*fra, ICOOADDY(cooi, 15), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Positions:", "OP");
	fra_put_string(*fra, ICOOADDY(cooi, 30), co, buffer);
	ft_sprintf(buffer, "%13s %s", "This frame:", "I");
	fra_put_string(*fra, ICOOADDY(cooi, 45), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Num-loop coef:", "-+");
	fra_put_string(*fra, ICOOADDY(cooi, 60), co, buffer);
/* 	ft_sprintf(buffer, "        (%d loops)", NLOOP); */
/* 	fra_put_string(*fra, ICOOADDY(cooi, 75), co, buffer); */
	return (0);
}

int	fra_set_defpos(t_fra *fra)
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

int	fra_set_cuspos1(t_fra *fra)
{
	fra->coo.x = STARTCAMX1;
	fra->coo.y = STARTCAMY1;
	fra->zoom = STARTZOOM1;
	fra->scdt.y = -1. / STARTZOOM1;
	fra->scdt.x = +1. / STARTZOOM1;
	fra_apply_zoom(fra, 1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_fra	fra;
	F_T		sierp_deltas[MAX_SIERP_LOOPS];

	test = 0;
	testn = 0;
	testtot = 0;
/* 	fra_read_input(ac, av, fra, frat); */
	ft_bzero(&fra, sizeof(t_fra));
	fra.sierp_deltas = (F_T*)&sierp_deltas;
	fra_init_env(&fra, 1);
	if (fra_init_window(&fra))
		return (1);
	fra_pause(&fra);
	(void)ac;
	(void)av;
	return (0);
}
